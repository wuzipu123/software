/*
 * conversion.h
 *
 *  Created on: 01.08.2019
 *      Author: tolotos
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_

#include <stdint.h>

extern void writeFloat(float value, uint32_t numDigits, char *valueString);
extern void writeInt(int value, uint32_t numDigits, char *valueString);

#endif /* CONVERSION_H_ */
