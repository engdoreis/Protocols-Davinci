/**
 * @file    TPDriver.h
 * @author  Douglas Reis
 * @date    07/07/2014
 * @version 1.0
 *
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef TPDriver_H_
#define TPDriver_H_

#include <stdint.h>

#include "../Settings.h"

typedef struct
{
	void * ( *Open)(const uint8_t*portName);
	uint16_t ( *Write)(void *handle, const void *buffer, uint16_t size);
	uint16_t ( *Read)(void *handle, void *buffer, uint16_t size);
	uint16_t ( *Close)(void *handle);
	void ( *Flush)(void *handle);
	uint32_t ( *Tick)();
	uint32_t ( *Sleep)();
} TPDriver;


#endif /* TPDriver_H_ */
