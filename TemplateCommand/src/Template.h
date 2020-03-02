/**
 * @file    GCP.h
 * @author  Douglas Reis
 * @date    30/03/2019
 * @version 1.0
 *
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 */

#ifndef T_NinebotH_
#define T_NinebotH_

#include <stdint.h>
#include <stdbool.h>

#include "CommandID.h"
#include "Result.h"

typedef void (*T_EventCallback)(void *param, uint8_t address, uint32_t event, uint16_t size, uint8_t *payload);

typedef struct T_Driver
{
	void *   ( *Open )(const uint8_t *portName);
	uint16_t ( *Write)(void *handle, const void *buffer, uint16_t size);
	uint16_t ( *Read )(void *handle, void *buffer, uint16_t size);
	uint16_t ( *Close)(void *handle);
	void     ( *Flush)(void *handle);
	uint32_t ( *Tick )();
	uint32_t ( *Sleep)();
}T_Driver;

typedef struct
{
	void *handle;
}T_Obj;


bool T_Run (T_Obj *ctx);

bool T_Init(T_Obj *ctx, const void *port, T_Driver *driver, uint8_t * buffer, uint32_t size);

Template_Result T_ClientGetBatteryStatus(T_Obj *ctx, BatteryStatus *status);

Template_Result T_ClientGetSpeed(T_Obj *ctx, uint8_t *speed);

Template_Result T_ClientSetLocked(T_Obj *ctx, bool lock);

Template_Result T_ClientSetHeadLight(T_Obj *ctx, bool enable);

Template_Result T_ClientGetLocked(T_Obj *ctx, bool *lock);

Template_Result T_ClientSetEnabled(T_Obj *ctx, bool enable);

Template_Result T_ClientGetEnabled(T_Obj *ctx, bool *enable);

Template_Result T_ClientGetMaximumSpeed(T_Obj *ctx, uint8_t *maxSpeed);

Template_Result T_ClientSetMaximumSpeed(T_Obj *ctx, uint8_t maxSpeed);

Template_Result T_ClientGetFirmwareVersion(T_Obj *ctx, uint8_t *major, uint8_t *minor, uint8_t *bugFix);

Template_Result T_ClientPlayBuzzer(T_Obj *ctx, uint16_t freq, uint16_t periondOn, uint16_t periodOff, uint16_t loop);

Template_Result T_ClientSetTimeout(T_Obj *ctx, uint16_t keepAliveTimeout, uint16_t watchdogTimeout);

Template_Result T_ClientUnlockBattery(T_Obj *ctx, bool unlock);

Template_Result T_ClientReset(T_Obj *ctx);

Template_Result T_ClientGetVehicleStatus(T_Obj *ctx, VehicleStatus *status);

#endif
