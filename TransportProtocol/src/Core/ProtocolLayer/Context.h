/**
 * @file    TP_Context.h
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

#ifndef TPCONTEXT_H_
#define TPCONTEXT_H_

#include <string.h>

#include "../ProtocolLayer/IState.h"
#include "../Type/Control.h"
#include "../Type/Driver.h"
#include "../Type/Frame.h"

typedef void (*ITPCallback)(void *param, uint8_t address, uint16_t size, uint8_t *payload);

struct TP_Context
{
	void *port;
	TPDriver driver;
	Frame command;
	Frame response;
	TPControl control;
	ITPCallback callback;
	void *param;
	ITPState state;
};

/*!
 * Metodo para reinicializar os atributos de controle da maquina de estado do protocolo.
 *
 * @param context Referencia do contexto da comunicacao para reinicializacao.
 */
void TPResetContext(TP_Context *context);


#endif /* TPCONTEXT_H_ */
