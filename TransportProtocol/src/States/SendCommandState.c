/**
 * @file    TPSendCommandState.h
 * @author  Douglas Reis
 * @date    02/10/2014
 * @version 1.0
 *
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 * 
 */
 
//
//void TPSendCommandState(TP_Context *context)
//{
//	if(TPSendFrame(context, &context->command) == false)
//	{
//		if(context->control.trialsAmount++ > TP_TRIALS_AMOUNT)
//		{
//			TPLog(0, "Erro na tentativa de envio");
//
//			TPResetContext(context);
//
//			context->control.status = TPErrorSending;
//			context->state = NULL;
//		}
//	}
//
//	else
//	{
//		context->state = TPIdleState;
//	}
//}
