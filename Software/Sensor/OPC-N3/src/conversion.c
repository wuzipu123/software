/*
 * conversion.c
 *
 *  Created on: 01.08.2019
 *      Author: tolotos
 */

#include "conversion.h"
#include "stdio.h"
#include "stdbool.h"

static void splitFloat(float value, uint32_t *integralPart, uint32_t *decimalPart);
static void intToChar(uint32_t value, uint32_t *numDigits, char **valueString, bool floatMode);

#define FLOAT_RESOLUTION	1e9
#define FLOAT_DIGITS		8

void writeFloat(float value, uint32_t numDigits, char *valueString)
{
	if (!numDigits)
	{
		return;
	}

	if (value < 0.0)
	{
		*valueString++ = '-';
		value = -value;
		numDigits--;
	}

	uint32_t integralPart, decimalPart;

	splitFloat(value, &integralPart, &decimalPart);

	intToChar(integralPart, &numDigits, &valueString, false);
	if (!numDigits--)
	{
		return;
	}

	*valueString++ = '.';

	if (decimalPart)
	{
		intToChar(decimalPart, &numDigits, &valueString, true);
	}

	while (numDigits--)
	{
		*valueString++ = '0';
	}
}

void writeInt(int value, uint32_t numDigits, char *valueString)
{
	if (!numDigits)
	{
		return;
	}

	if (value < 0)
	{
		*valueString++ = '-';
		value = -value;
		numDigits--;
	}

	intToChar(value, &numDigits, &valueString, false);
}

void splitFloat(float value, uint32_t *integralPart, uint32_t *decimalPart)
{
	*integralPart = (uint32_t)value;
	float remainder = value - *integralPart;

	remainder *= FLOAT_RESOLUTION;
	*decimalPart = (uint32_t)remainder;
}

void intToChar(uint32_t value, uint32_t *numDigits, char **valueString, bool floatMode)
{
	if (!*numDigits)
	{
		return;
	}

	uint32_t digit = 0;
	const uint32_t expLookup[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

	if(floatMode)
	{
		uint32_t zeroCounter = FLOAT_DIGITS;
		uint32_t tempValue = value / expLookup[zeroCounter];
		while(tempValue == 0)
		{
			**valueString = (char)(digit + 0x30);
			(*valueString)++;
			tempValue = value / expLookup[--zeroCounter];
		}
	}

	//Calculate number of used digits
	uint32_t tempValue = value;
	uint32_t numIntDigits = 0;
	while (tempValue != 0)
	{
		tempValue = tempValue / 10;
		numIntDigits++;
	}

	//Insert leading zeros
	uint32_t numZeroDigits = 0;
	while ((*numDigits-numIntDigits)-numZeroDigits)
	{
		**valueString = (char)'0';
		(*valueString)++;
		numZeroDigits++;
	}

	//Convert decimal positions to chars
	for (; numIntDigits; numIntDigits--)
	{
		digit = (value / expLookup[numIntDigits-1]);
		**valueString = (char)(digit + 0x30);
		(*valueString)++;
		value -= digit * expLookup[numIntDigits-1];

		if (!--(*numDigits))
		{
			return;
		}
	}
}
