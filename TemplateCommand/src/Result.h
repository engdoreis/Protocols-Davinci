/*
 * Template_Result.h
 *
 *  Created on: 5 de abr de 2019
 *      Eng. Douglas Reis
 */

#ifndef SRC_Template_Result_H_
#define SRC_Template_Result_H_
typedef enum __attribute__ ((__packed__))
{
	T_OK = 0x00,
	T_NotAvailable                   ,
	T_Timeout                        ,
	T_ProtocolError                  ,
	T_NotOpenError                   ,
	T_ParameterError                 ,
	T_GeneralError = 0xFF
}Template_Result;


#endif /* SRC_Template_Result_H_ */
