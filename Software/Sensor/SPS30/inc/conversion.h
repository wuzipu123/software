/*
 * conversion.h
 *
 *  Created on: 01.08.2019
 *      Author: tolotos
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_

#include <stdint.h>

/**
 * \brief Converts a float value to a string.
 *
 * \param value Integer value to write.
 * \param numDigits The maximum number of characters possible to write into the buffer.
 * \param valueString Pointer holding the current writing position in the buffer.
 */
extern void writeFloat(float value, uint32_t numDigits, char *valueString);

/**
 * \brief Converts an integer value to a string.
 *
 * \param value Integer value to write.
 * \param numDigits The maximum number of characters possible to write into the buffer.
 * \param valueString Pointer holding the current writing position in the buffer.
 */
extern void writeInt(int value, uint32_t numDigits, char *valueString);

#endif /* CONVERSION_H_ */
