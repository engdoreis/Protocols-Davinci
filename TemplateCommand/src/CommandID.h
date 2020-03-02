/*
 * T_CommandID.h
 *
 *  Created on: 5 de abr de 2019
 *      Eng. Douglas Reis
 */

#ifndef SRC_T_COMMANDID_H_
#define SRC_T_COMMANDID_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
		T_CmdGetBatteryStatus,
		T_CmdGetSpeed,
		T_CmdSetLocked,
		T_CmdGetLocked,
		T_CmdSetEnabled,
		T_CmdGetEnabled,
		T_CmdSetMaxSpeed,
		T_CmdGetMaxSpeed,
		T_CmdGetFirmwareVersion,
		T_CmdPlayBuzzer,
		T_CmdSetTimeout,
		T_CmdUnlockBattery,
		T_CmdReset,
		T_CmdKeepAlive
}T_CommandID;


typedef struct
{
	bool charging;
	uint8_t charge;
	uint16_t voltage;
}BatteryStatus;


typedef struct
{
	uint8_t vehicleSerialNumber[32];
	uint8_t batterySerialNumber[32];
	uint8_t name[32];
	uint32_t errorCode;
	uint32_t alarmCode;
	uint8_t operationMode;
	uint32_t speed;
	uint32_t mileage;
	uint32_t operationTime;
	uint32_t ridingTime;
	float drivingVoltage;
	float systemCurrent;
	float motorFaseCurrent;
	bool isBatteryCharging;
	uint8_t batteryCharge;
	float batteryVoltage;
	float batteryCurrent;
	int16_t batteryTemperature;
	uint16_t batteryCycles;
	uint16_t batteryCharges;
	uint16_t batteryCellAmount;
	float batteryCellVoltage[50];
}VehicleStatus;

#endif /* SRC_T_COMMANDID_H_ */
