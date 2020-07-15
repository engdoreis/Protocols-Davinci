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

#include <Frame.h>
#include <Template.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#ifndef __LITTLE_ENDIAN__
#define __LITTLE_ENDIAN__
#endif
#endif

/*!
 * @internal
 * @private
 */
typedef struct
{
	TP_Obj * tp;
	T_Callback eventCallback;
	void * eventArg;
	T_Callback commandCallback;
	void * commandArg;
	T_Callback responseCallback;
	void * responseArg;
	T_Frame * frame;
	uint32_t payloadSize;
	uint8_t transferSeq;
	uint8_t address;
	uint8_t * workBuffer;
	uint16_t  workBufferLen;
	bool waitingResponse;
}T_Context;


#define T_SET_FRAME_HEADER(f, t, i, s) \
	f->type = t;\
	f->id = i;\
	f->statusCode = s;

#define T_FRAME_HEADER_SIZE (uint32_t)(&(((T_Frame *)0)->payload))
#define T_MAX_PAYLOAD_LEN (uint32_t)128

#ifdef __LITTLE_ENDIAN__



#else


#endif

#endif /* SRC_T_TYPES_H_ */
