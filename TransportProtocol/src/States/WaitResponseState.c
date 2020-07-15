/**
 * @file   TPWaitResponseState.c
 * @Author Douglas Reis
 * @date   04/10/2014
 */

#include "../../Core/States/State.h"


//void TPWaitResponseState(TP_Context *context)
//{
	/*
	context->control.bytesRead += IRead((void *)context->buffer, 1);

	if (context->control.bytesRead > 0)
	{
		if (context->buffer[0] == TPACK)
		{
			TPResetContext(context);

			context->state = NULL;
		}

		else if (context->buffer[0] == TPNAK)
		{
			context->control.timeout = 0;
			context->control.waitResponseAmount = 0;

			context->state = TPNAKResponseState;
		}

		else if (context->buffer[0] == TPWait)
		{
			if (context->control.waitResponseAmount++ > TP_WAIT_AMOUNT)
			{
				TPLog(0, "Excedeu o numero de Waits recebidos");

				TPResetContext(context);

				context->state = NULL;
			}

			else
			{
				context->control.timeout = 0;
			}
		}

		else
		{
			TPLog(0, "Quebra de Sequencia");

			TPResetContext(context);

			context->state = TPIdleState;
		}
	}

	else
	{
		if (++context->control.timeout > TP_WAIT_TIMEOUT)
		{
			TPLog(TPTimeout, "Wait Timeout");

			TPResetContext(context);

			context->control.status = TPTimeout;
			context->state = NULL;
		}
	}
	*/
//}
