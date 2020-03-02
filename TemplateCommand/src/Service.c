/*
 ============================================================================
 Name        : T_NinebotServer.c
 Author      : Douglas Reis
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include <TransportProtocol.h>

#include "CommandID.h"

#include "types.h"
#include "Template.h"

void TP_Callback(void *param, uint8_t address, uint16_t size, uint8_t *payload)
{
	T_Context * ctx = param;
	ctx->frame = (T_Frame *) payload;
	ctx->waitingResponse = false;
}

bool T_Init(T_Obj *obj, const void *port, T_Driver *driver, uint8_t * buffer, uint32_t size)
{
	TP_ASSERT(obj == NULL || port == NULL || buffer == NULL);

	uint32_t offset = 0;
	obj->handle = buffer;
	T_Context * ctx = obj->handle;
	offset += sizeof(T_Context);
	TP_ASSERT(offset >= size);

	ctx->workBufferLen = T_FRAME_HEADER_SIZE + T_MAX_PAYLOAD_LEN;
	ctx->workBuffer = buffer + offset;
	offset += ctx->workBufferLen;
	TP_ASSERT(offset >= size);

	ctx->tp = (TP_Obj * )buffer + offset;
	offset += sizeof(TP_Obj);
	TP_ASSERT(offset >= size);

	bool ret = TP_Init(ctx->tp, (TPDriver *)driver, TP_Callback, ctx, 2000, buffer + offset, size - offset);
	if(ret)
	{
		ctx->address = 0;
	}

	end:
	return ret;
}

Template_Result T_KeepAlive(T_Obj *obj)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{
		T_Frame * frame = (T_Frame *) ctx->workBuffer;
		T_SET_FRAME_HEADER(frame, T_FrameCommand, T_CmdKeepAlive, T_OK, 0);

		TP_Send(ctx->tp, ctx->address, (uint8_t *)frame, T_FRAME_HEADER_SIZE);
	}
	return result;
}

Template_Result T_GetBatteryStatus(T_Obj *obj, BatteryStatus *status)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx && status)
	{
		T_Frame * frame = (T_Frame *) ctx->workBuffer;
		T_SET_FRAME_HEADER(frame, T_FrameCommand, T_CmdGetBatteryStatus, T_OK, 0);

		memset(status, 0, sizeof(BatteryStatus));
		T_KeepAlive(obj);

		if(TP_Send(ctx->tp, ctx->address, (uint8_t *)frame, T_FRAME_HEADER_SIZE) == true)
		{
			uint32_t tries = 3;
			ctx->frame = NULL;
			result = T_ProtocolError;
			ctx->waitingResponse = true;
			do
			{
				TP_Process(ctx->tp);
				if(!ctx->waitingResponse && ctx->frame && ctx->frame->type == T_FrameResponse && ctx->frame->id == T_CmdGetBatteryStatus)
				{
					uint32_t size = T_GET_PAYLOAD_SIZE(ctx->frame);
					result = (Template_Result)frame->statusCode;
					memcpy(status, frame->payload, size);
					break;
				}
				tries--;
			}while(tries);
		}
	}
	return result;
}

Template_Result T_GetSpeed(T_Obj *obj, uint8_t *speed)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx && speed)
	{

	}
	return result;
}

Template_Result T_SetLocked(T_Obj *obj, bool lock)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_SetHeadLight(T_Obj *obj, bool enable)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{
	}
	return result;
}

Template_Result T_GetLocked(T_Obj *obj, bool *lock)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx && lock)
	{
	}

	return result;
}

Template_Result T_SetEnabled(T_Obj *obj, bool enable)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_GetEnabled(T_Obj *obj, bool *enable)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_GetMaximumSpeed(T_Obj *obj, uint8_t *maxSpeed)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_SetMaximumSpeed(T_Obj *obj, uint8_t maxSpeed)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_GetFirmwareVersion(T_Obj *obj, uint8_t *major, uint8_t *minor, uint8_t *bugFix)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_PlayBuzzer(T_Obj *obj, uint16_t freq, uint16_t periondOn, uint16_t periodOff, uint16_t loop)
{
	Template_Result result = T_ParameterError;

	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_SetTimeout(T_Obj *obj, uint16_t keepAliveTimeout, uint16_t watchdogTimeout)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_UnlockBattery(T_Obj *obj, bool unlock)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_Reset(T_Obj *obj)
{
	Template_Result result = T_ParameterError;
	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}

Template_Result T_GetVehicleStatus(T_Obj *obj, VehicleStatus *status)
{
	Template_Result result = T_ParameterError;

	T_Context * ctx = obj->handle;

	if(ctx)
	{

	}
	return result;
}
