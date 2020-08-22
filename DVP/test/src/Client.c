/*!
 * @file main.c
 *
 *  @date Jul 11, 2020
 *  @author Douglas Reis
 */

#include <DVP.h>
#include "Porting.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define TIMEOUT 5000

struct ArrayWrapper
{
	uint32_t param[64];
};

typedef DVP_StatusCode (*Function)(DVP_Obj *, void *);
typedef struct
{
	char * name;
	Function function;
	bool isAsync;
	bool isReadable;
	int dataSize;
	char * outputFormat;
	char * inputFormat;
}TestCase;

TestCase TestMap[] =
{
	{"DVP_ReadVehicleStatus"     ,(Function)DVP_ReadVehicleStatus       ,false ,true ,sizeof(DVP_VehicleStatus)             ,"Ret=%u\r\n WheelLock=%hhx\r\n poweredOn=%hhx\r\n headLightOn=%hhx\r\n tailLightOn=%hhx\r\n buzzerOn=%hhx\r\n cruiseOn=%hhx\r\n speed=%hu", " "},
	{"DVP_WriteVehicleStatus"    ,(Function)DVP_WriteVehicleStatus      ,false ,true ,sizeof(DVP_VehicleStatus)             ,"Ret=%u", "WheelLock=%hhx\r\n poweredOn=%hhx\r\n headLightOn=%hhx\r\n tailLightOn=%hhx\r\n buzzerOn=%hhx\r\n cruiseOn=%hhx\r\n speed=%hu"},
	{"DVP_ReadVehicleConfig"     ,(Function)DVP_ReadVehicleConfig       ,false ,true ,sizeof(DVP_VehicleConfig)             ,"Ret=%u\r\n cruiseEnabled=%hhx\r\n throttleLevel=%hhx\r\n brakeLevel=%hhx\r\n startSpeed=%hu\r\n speedLimit=%hu\r\n", " "},
	{"DVP_WriteVehicleConfig"    ,(Function)DVP_WriteVehicleConfig      ,false ,true ,sizeof(DVP_VehicleConfig)             ,"Ret=%u", "cruiseEnabled=%hhx\r\n throttleLevel=%hhx\r\n brakeLevel=%hhx\r\n startSpeed=%hu\r\n speedLimit=%hu\r\n"},
	{"DVP_ReadVehicleInfo"       ,(Function)DVP_ReadVehicleInfo         ,false ,true ,sizeof(DVP_Info)                      ,"Ret=%u\r\n serialnumber=%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X\r\n firmwareVersion=%hhX.%hhX.%hhX.%hhX\r\n", " "},
	{"DVP_ReadBatteryStatus"     ,(Function)DVP_ReadBatteryStatus       ,false ,true ,sizeof(DVP_BatteryStatus)             ,"Ret=%u\r\n isCharging=%hhx\r\n charge=%hhu%%\r\n temperature=%hhu�c\r\n voltage=%huV\r\n", " "},
	{"DVP_ReadBatteryInfo"       ,(Function)DVP_ReadBatteryInfo         ,false ,true ,sizeof(DVP_Info)                      ,"Ret=%u\r\n serialnumber=%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X%hh02X\r\n firmwareVersion=%hhX.%hhX.%hhX.%hhX\r\n", " "},
	{"DVP_FirmwareUpdateStart"   ,(Function)DVP_FirmwareUpdateStart     ,false ,true ,sizeof(DVP_FirmwareUpdateStartPacket) ,"Ret=%u", "firmwareSize=%u\r\n"},
	{"DVP_FirmwareUpdateLoad"    ,(Function)DVP_FirmwareUpdateLoad      ,false ,true ,sizeof(DVP_FirmwareUpdateLoadPacket)  ,"Ret=%u", "sequence=%hu\r\n size=%hu\r\n content=%s\r\n"},
	{"DVP_FirmwareUpdateFinish"  ,(Function)DVP_FirmwareUpdateFinish    ,false ,true ,sizeof(DVP_FirmwareUpdateFinishPacket),"Ret=%u", "crc=%04X\r\n version=%hhX.%hhX.%hhX.%hhX\r\n"},
	{"DVP_StartAuthentication"   ,(Function)DVP_StartAuthentication     ,false ,true ,sizeof(DVP_AuthenticationData)        ,"size=%hhu\r\n AuthData=%X %X %X %X %X %X %X %X\r\n", "Ret=%u"},
	{"DVP_Authenticate"          ,(Function)DVP_Authenticate            ,false ,true ,sizeof(DVP_AuthenticationData)        ,"Ret=%u", "size=%hhu\r\n AuthData=%X %X %X %X %X %X %X %X\r\n"},
	{"DVP_UpdatePublicKey"       ,(Function)DVP_UpdatePublicKey         ,false ,true ,sizeof(DVP_AuthenticationData)        ,"Ret=%u", "size=%hhu\r\n AuthData=%X %X %X %X %X %X %X %X\r\n"},

};

TestCase * GetTestCase(char * name)
{
	for(int i = 0; i < sizeof(TestMap)/sizeof(TestMap[0]); i++)
	{
		if(strcmp(TestMap[i].name, name) == 0)
		{
			return &TestMap[i];
		}
	}
	return NULL;
}

typedef struct
{
	DVP_Obj obj;
	bool running;
	DVP_Frame * frame;
	DVP_StatusCode status;
	uint32_t timeout;
}ClassTest;

DVP_Driver driver =
{
		.Open = UART_Open,
		.Write = UART_Write,
		.Read = UART_Read,
		.Close = UART_Close,
		.Flush = UART_Flush,
		.Tick = SYS_Tick,
		.Sleep = SYS_Sleep
};
uint32_t VA_ArgsGetSize(char * format)
{
	uint32_t size = 0;
	if(memcmp(format, "ll", 2) == 0)
	{
		size = sizeof(uint64_t);
	}else if(memcmp(format, "l", 1) == 0)
	{
		size = sizeof(uint32_t);
	}else if(memcmp(format, "hh", 2) == 0)
	{
		size = sizeof(uint8_t);
	}else if(memcmp(format, "h", 1) == 0)
	{
		size = sizeof(uint16_t);
	}else if( !memcmp(format, "u", 1) || !memcmp(format, "d", 1) || !memcmp(format, "x", 1) || !memcmp(format, "X", 1) || !memcmp(format, "i", 1) )
	{
		size = sizeof(uint32_t);
	}
	return size;
}

void VA_ArgsPrintfConverter(char * format, int ret, void * stack, uint32_t * output, uint32_t size)
{

	char template[512];
	uint32_t index = 0;
	strcpy(template, format);

	char *tok = strtok(template, "%");
	tok = strtok (NULL, "%");
	output[index++] = ret;
	tok = strtok (NULL, "%");

	while(tok && index < size)
	{
		if(memcmp(tok, "ll", 2) == 0)
		{
			output[index++] = *((uint64_t *)stack);
			stack += sizeof(uint64_t);
		}else if(memcmp(tok, "l", 1) == 0)
		{
			output[index++] = *((uint32_t *)stack);
			stack += sizeof(uint32_t);
		}else if(memcmp(tok, "hh", 2) == 0)
		{
			output[index++] = *((uint8_t *)stack);
			stack += sizeof(uint8_t);
		}else if(memcmp(tok, "h", 1) == 0)
		{
			output[index++] = *((uint16_t *)stack);
			stack += sizeof(uint16_t);
		}else if( !memcmp(tok, "u", 1) || !memcmp(tok, "d", 1) || !memcmp(tok, "x", 1) || !memcmp(tok, "X", 1) || !memcmp(tok, "i", 1) )
		{
			output[index++] = *((uint32_t *)stack);
			stack += sizeof(uint32_t);
		}
		tok = strtok (NULL, "%");
	}
}

void VA_ArgsScanfConverter(char * format, void * stack, uint32_t * output, uint32_t size)
{

	char template[512];
	uint32_t index = 0;
	strcpy(template, format);

	char *tok = strtok(template, "%");
	tok = strtok (NULL, "%");

	while(tok && index < size)
	{
		output[index++] = (uint32_t )stack;

		stack += VA_ArgsGetSize(tok);

		tok = strtok (NULL, "%");
	}
}

void Response(void *param, uint8_t address, DVP_Frame *data)
{
	ClassTest *test = (ClassTest*) param;

	test->timeout = SYS_Tick() + TIMEOUT;

	test->frame = data;

	test->status = data->statusCode;
	test->running = false;
}

void Event(void *param, uint8_t address, DVP_Frame *data)
{
	ClassTest *test = (ClassTest*) param;

	test->timeout = SYS_Tick() + TIMEOUT;

	test->frame = data;

	test->status = data->statusCode;
	test->running = false;
}

int main (int argc, char** argv)
{

	uint8_t buffer[1024], testBuffer[512];
	size_t size = 0;
	ClassTest test =
	{
			.running = true,
			.obj = {0},
	};

	if(argc < 4)
		return 1;

	//Disable stdout buffer to flush immediately
	setvbuf(stdout, NULL, _IONBF, 0);

	bool ret = DVP_Init(&test.obj, "client:1001", &driver, buffer, sizeof(buffer));
	test.timeout = SYS_Tick() + TIMEOUT;

	if (ret)
	{
		struct ArrayWrapper array;
		TestCase *tc;
		ret = DVP_RegisterResponseCallback(&test.obj, Response, &test);
		ret = DVP_RegisterEventCallback(&test.obj, Event, &test);


		printf("Test: %s\r\n ", argv[1]);
		tc = GetTestCase(argv[1]);
		if(tc == NULL)
		{
			printf("Test %s not found\r\n ", argv[1]);
			return 2;
		}

		printf("\r\n Opening: %s\r\n ", argv[2]);
		FILE *fp = fopen(argv[2], "rb");
		if(fp)
		{
			VA_ArgsScanfConverter(tc->inputFormat, testBuffer, array.param, sizeof(array.param) / sizeof(array.param[0]));
			fscanf(fp, tc->inputFormat, array);

			fclose(fp);

			if(size < tc->dataSize)
			{
				printf("Wrong data size\r\n ");
			}
		}

		printf("Sending\r\n ");
		if(tc->isAsync)
		{
			test.status = tc->function(&test.obj, testBuffer);
			test.running = true;
			test.status = DVP_TimeoutError;
			while(test.running)
			{
				DVP_Run(&test.obj);
				if(	test.timeout < SYS_Tick())
				{
					printf("Timeout\r\n ");
					return 2;
				}
			}
			memcpy(testBuffer, test.frame->payload.raw, tc->dataSize);
		}
		else
		{
			test.status = tc->function(&test.obj, testBuffer);
		}

		printf("\r\n Opening: %s\r\n ", argv[3]);
		fp = fopen(argv[3], "w");
		if(fp)
		{
			VA_ArgsPrintfConverter(tc->outputFormat, test.status, testBuffer, array.param, sizeof(array.param) / sizeof(array.param[0]));
			fprintf(fp, tc->outputFormat, array);
			fclose(fp);
		}
	}

	return 0;
}
