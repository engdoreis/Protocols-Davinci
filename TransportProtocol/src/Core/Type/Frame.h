/**
 * @file    Frame.h
 * @author  Douglas Reis
 * @date    05/06/2014
 * @version 1.0
 *
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 *
 */

#ifndef Frame_H_
#define Frame_H_

#include <stdint.h>
#include "../Settings.h"

#pragma pack(push,1)

typedef struct
{
	uint8_t stx[2];				/*!< Start of Text */
	uint8_t address;			/*!< Start of Text */
	uint8_t size[2];
	uint8_t *data;
	uint8_t crc[2];
}Frame;

#pragma pack(pop)

static const uint8_t TP_STX[] = {0x5A, 0x55};

#define TP_STX_SIZE	          	sizeof(TP_STX)
#define TP_STARTING_FRAME_SIZE	(uint32_t)(&(((Frame *)0)->data))
#define TP_CRC_SIZE		  		sizeof(((Frame*)0)->crc)

#endif /* Frame_H_ */
