/*
 * Ninebot_types.h
 *
 *  Created on: Sep 25, 2019
 *      Eng. Douglas Reis
 */

#ifndef SRC_T_TYPES_H_
#define SRC_T_TYPES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <Template.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#ifndef __LITTLE_ENDIAN__
#define __LITTLE_ENDIAN__
#endif
#endif

#pragma pack(push,1)

typedef enum
{
	T_FrameCommand,
	T_FrameResponse,
	T_FrameEvent,
}T_FrameType;

typedef struct
{
	T_FrameType type;
	T_CommandID id;
	Template_Result    statusCode;
	uint8_t       length[2];
	uint8_t       payload[(2 ^ 16) - 1];
}T_Frame;

typedef struct
{
	TP_Obj * tp;
	T_EventCallback eventCallback;
	T_Frame * frame;
	uint8_t transferSeq;
	uint8_t address;
	uint8_t * workBuffer;
	uint16_t  workBufferLen;
	bool waitingResponse;
}T_Context;


#define T_SET_FRAME_HEADER(f, t, i, s, l) \
	f->type = t;\
	f->id = i;\
	f->statusCode = s;\
	TP_Int16ToArray(l, f->length)


#define T_GET_PAYLOAD_SIZE(f) TP_CRC_ArrayToInt(f->length)


#define T_FRAME_HEADER_SIZE (uint32_t)(&(((T_Frame *)0)->payload))
#define T_MAX_PAYLOAD_LEN (uint32_t)128

#ifdef __LITTLE_ENDIAN__



#else


#endif

#pragma pack(pop)
#endif /* SRC_T_TYPES_H_ */
