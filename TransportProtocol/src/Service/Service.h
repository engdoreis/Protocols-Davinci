/**
 * @file   TPService.h
 * @Author Douglas Reis
 * @date   02/10/2014
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */

#ifndef TPSERVICE_H_
#define TPSERVICE_H_

#include "../Core/Core.h"
#include "../Core/Helper/Helper.h"
#include "../Core/ProtocolLayer/Context.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	void *handle;
}TP_Obj;

bool TP_Init(TP_Obj *obj, TPDriver *driver, ITPCallback callback, void *param, uint32_t timeout, uint8_t *buffer, uint32_t size);

bool TP_Send(TP_Obj *obj, uint8_t address, const uint8_t *payload, uint32_t size);

void TP_Process(TP_Obj *obj);

#ifdef __cplusplus
}
#endif


#endif /* TPSERVICE_H_ */
