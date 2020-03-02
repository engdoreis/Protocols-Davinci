/**
 * @file    TPControl.h
 * @author  Douglas Reis
 * @date    10/07/2014
 * @version 1.0
 *
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef TPCONTROL_H_
#define TPCONTROL_H_

#include "../Settings.h"
#include "Status.h"


typedef struct TPControl
{
	void *handle;
	uint32_t timeoutConfig;
	uint32_t timeout;
	uint32_t bytesRead;
	uint8_t trialsAmount;
	uint32_t size;	             			/*!< Maximum payload size */
	uint32_t maxPayloadSize;				/*!< Maximum payload size */
	TPStatus status;
} TPControl;


#endif /* TPCONTROL_H_ */
