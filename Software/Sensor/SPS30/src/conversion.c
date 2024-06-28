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

static void integralToChar(uint32_t value, uint32_t *numDigits, char **valueString, bool leadingZeros);
static void decimalToChar(uint32_t value, uint32_t *numDigits, char **valueString);
static void integerToChar(uint32_t value, char **valueString, uint32_t numIntDigits, uint32_t *numDigits);

#define FLOAT_RESOLUTION	1e9
#define FLOAT_DIGITS		8

static const uint32_t expLookup[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};


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

	integralToChar(integralPart, &numDigits, &valueString, false);

	if (!numDigits--)
	{
		return;
	}

	*valueString++ = '.';

	if (decimalPart)
	{
		decimalToChar(decimalPart, &numDigits, &valueString);
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

	integralToChar(value, &numDigits, &valueString, true);
	if (!numDigits--)
	{
		return;
	}

	while (numDigits--)
	{
		*valueString++ = '0';
	}
}

/**
 * \brief Splits a float number from \ref value in its \ref integralParts and \ref decimalParts.
 *
 * \param value Integer value to write.
 * \param integralPart Pointer to the integer value of the integral part of the float \ref value.
 * \param decimalPart Pointer to the integer value of the decimal part of the float \ref value.
 */
void splitFloat(float value, uint32_t *integralPart, uint32_t *decimalPart)
{
	*integralPart = (uint32_t)value;
	float remainder = value - *integralPart;

	remainder *= FLOAT_RESOLUTION;
	*decimalPart = (uint32_t)remainder;
}

/**
 * \brief Writes the \ref integralPart of a float value in a character buffer.
 *
 * \param value Integer value to write.
 * \param numDigits  Pointer to the maximum number of characters possible to write into the buffer.
 * \param valueString Pointer to pointer holding the current writing position in the buffer.
 * \param leadingZeros A bool variable to check if there are leading zeros or not.
 */
void integralToChar(uint32_t value, uint32_t *numDigits, char **valueString, bool leadingZeros)
{
	uint32_t tempValue = value;
	uint32_t numIntDigits = 0;

	if (!*numDigits)
	{
		return;
	}

	while (tempValue != 0)
	{
		tempValue = tempValue / 10;
		numIntDigits++;
	}

	//Insert leading zeros
	if(leadingZeros)
	{
		uint32_t numZeroDigits;

		if(*numDigits > numIntDigits)
		{
			numZeroDigits = *numDigits - numIntDigits;
		}
		else
		{
			numZeroDigits = *numDigits;
		}

		while (numZeroDigits--)
		{
			**valueString = '0';
			(*valueString)++;
			(*numDigits)--;
		}
	}
	else
	{
		if(!value)
		{
			**valueString = '0';
		    (*valueString)++;
		    (*numDigits)--;
		    return;
		}
	}

	integerToChar(value, valueString, numIntDigits, numDigits);
}

/**
 * \brief Writes the \ref integralPart of a float value in a character buffer.
 *
 * \param value Integer value to write.
 * \param numDigits Pointer to the maximum number of characters possible to write into the buffer.
 * \param valueString Pointer to pointer holding the current writing position in the buffer.
 */
void decimalToChar(uint32_t value, uint32_t *numDigits, char **valueString)
{
	uint32_t tempValue = value;
	uint32_t numIntDigits = 0;

	if (!*numDigits)
	{
		return;
	}

	while (tempValue != 0)
	{
		tempValue = tempValue / 10;
		numIntDigits++;
	}

	uint32_t zeroCounter = FLOAT_DIGITS;
	tempValue = value / expLookup[zeroCounter];
	while (tempValue == 0)
	{
		**valueString = '0';
		(*valueString)++;
		tempValue = value / expLookup[--zeroCounter];

		if (!--(*numDigits))
		{
			return;
		}
	}

	integerToChar(value, valueString, numIntDigits, numDigits);
}

/**
 * \brief Write a given Integer as string into a character buffer.
 *
 * \param value Integer value to write.
 * \param valueString Pointer to pointer holding the current writing position in the buffer.
 * \param numIntDigits Number of digits of \ref value.
 * \param numDigits Pointer to the maximum number of characters possible to write into the buffer.
 */
void integerToChar(uint32_t value, char **valueString, uint32_t numIntDigits, uint32_t *numDigits)
{
	char digit;

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

