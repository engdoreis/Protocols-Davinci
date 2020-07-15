/*!
 * @file main.c
 *
 *  @date Jul 11, 2020
 *  @author Douglas Reis
 */

#include <Template.h>
#include "Porting.h"
#include <stdio.h>

#define TIMEOUT 2000

typedef struct
{
	T_Obj obj;
	bool running;
	uint8_t payload[1024];
	uint32_t size;
	uint32_t timeout;
}ClassServerTest;

T_Driver driver =
{
		.Open = UART_Open,
		.Write = UART_Write,
		.Read = UART_Read,
		.Close = UART_Close,
		.Flush = UART_Flush,
		.Tick = SYS_Tick,
		.Sleep = SYS_Sleep
};

void Command(void *param, uint8_t address, T_Frame *data)
{
	ClassServerTest *test = (ClassServerTest*) param;

	test->timeout = SYS_Tick() + TIMEOUT;
	switch(data->id)
	{
	case T_Cmd1:
	{
		st_cmd1 cmd1;
		cmd1.field1 = data->payload.cmd1.field1 + 1;
		cmd1.field2 = data->payload.cmd1.field2 + 2;
		T_Response1(&test->obj, T_OK, &cmd1);
	}break;
	case T_Cmd2:
	{
		T_Response2(&test->obj, T_NotSupportedError, NULL);
	}break;
	default:
		break;
	}
}

void Event(void *param, uint8_t address, T_Frame *data)
{
	ClassServerTest *test = (ClassServerTest*) param;

	test->timeout = SYS_Tick() + TIMEOUT;
	switch(data->id)
	{
	case T_Evt1:
	{
		st_cmd2 evt;
		evt.field1 = data->payload.cmd1.field1 + 1;
		evt.field2 = data->payload.cmd1.field2 + 2;
		evt.field3 = ((data->payload.cmd1.field2 - 1) << 8) | ((data->payload.cmd1.field2 - 2) << 0);
		T_Event2(&test->obj, &evt);
	}break;
	default:
		break;
	}
}

int main (int argc, char** argv)
{

	uint8_t buffer[512];
	ClassServerTest test =
	{
			.running = true,
			.obj = {0}
	};

	//Disable stdout buffer to flush immediately
	setvbuf(stdout, NULL, _IONBF, 0);

	bool ret = T_Init(&test.obj, "server:1003", &driver, buffer, sizeof(buffer));
	if (!ret)
		goto exit;

	ret = T_RegisterCommandCallback(&test.obj, Command, &test);
	ret = T_RegisterEventCallback(&test.obj, Event, &test);


	test.timeout = SYS_Tick() + TIMEOUT;
	while(test.timeout > SYS_Tick())
	{
		ret = T_Run(&test.obj);
	}

	exit:
	return 0;
}
