/*!
 * @file    Template.h
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

#include "PacketID.h"
#include "Frame.h"
#include "StatusCode.h"
/*!
 * @defgroup API
 */


/*! @defgroup InitAPI Initialization API
 *  @brief This API is used to initialize the library in order to use the specifics APIs.
 *  @ingroup API
 *  @{
 */

typedef void (*T_Callback)(void *param, uint8_t address, T_Frame *data);

/*!
 * @brief Callback struct to provide access to platform resources.
 */ 
typedef struct T_Driver
{
	/*!
	 * @brief Open the port and return a handler to used by the functions T_Driver::Write T_Driver::Read T_Driver::Close
	 *
	 * @param[in] portName Name or identification to port to be opened.
	 *
	 * @return Handler to used to used by the functions T_Driver::Write T_Driver::Read T_Driver::Close
	 */
	void * ( *Open )(const void *portName);

	/*!
	 * @brief Write raw data to port opened by T_Driver::Open
	 *
	 * @param[in] handle Returned by T_Driver::Open.
	 * @param[in] buffer Buffer with the data to be send.
	 * @param[in] size   Amount of data so be send.
	 *
	 * @return Amount of data written.
	 */
	uint16_t ( *Write)(void *handle, const void *buffer, uint16_t size);

	/*!
	 * @brief Read raw data from port opened by T_Driver::Open
	 *
	 * @param[in] handle Returned by T_Driver::Open.
	 * @param[in] buffer Memory buffer to receive the data read.
	 * @param[in] size   Total space available in the buffer.
	 *
	 * @return Amount of data read.
	 */
	uint16_t ( *Read )(void *handle, void *buffer, uint16_t size);

	/*!
	 * @brief Close the port opened by T_Driver::Open
	 *
	 * @param[in] handle Returned by T_Driver::Open.
	 *
	 * @return 0 if ok.
	 */
	uint16_t ( *Close)(void *handle);

	/*!
	 * @brief Flush the port opened by T_Driver::Open
	 *
	 * @param[in] handle Returned by T_Driver::Open.
	 *
	 */
	void     ( *Flush)(void *handle);

	/*!
	 * @brief Read the system tick.
	 *
	 * @return System tick.
	 */
	uint32_t ( *Tick )();

	/*!
	 * @brief Sleep during the time specified.
	 *
	 * @param[in] time to sleep
	 */
	void (*Sleep) (uint32_t time);
}T_Driver;

/*!
 * @brief Class to hold the execution context.
 *
 * @details Must be allocated by the application.
 * @code{.cpp}
 * void main(void)
 * {
 *    uint8_t buffer[1024];
 *    T_Obj obj;
 *    T_Init(&obj, "COM1", &driver, buffer, sizeof(buffer));
 * ...
 * }
 * @endcode
 *
 */
typedef struct
{
	void *handle;
}T_Obj;

/*!
 * @brief Initialize the library
 *
 * @param[out] obj Pointer to the object which will be initialized.
 * 
 * @return ::Template_Result
 */
bool T_Init(T_Obj *obj, const void *port, T_Driver *driver, uint8_t * buffer, uint32_t size);

/*!
 * @brief Register a callback to receive notifications when a event arrives.
 *
 * @details The only way to receive event is by registering this callback, other wise the even
 * will be just discarded.
 * The function ::T_Run must be often called to provide processing time to the library.
 *
 * @param obj       Pointer to the object initialized in ::T_Init function.
 * @param callback  Pointer to function to receive the events
 * @param arg       Pointer that will used as the first parameter of callback.
 * @return
 */
bool T_RegisterEventCallback(T_Obj *obj, T_Callback callback, void *arg);

/*!
 * @brief Register a callback to receive notifications when a command arrives.
 *
 * @details Setting this callback the Async functions are enabled.
 * The function ::T_Run must be often called to provide processing time to the library.
 *
 * @param obj       Pointer to the object initialized in ::T_Init function.
 * @param callback  Pointer to function to receive the responses.
 * @param arg       Pointer that will used as the first parameter of callback.
 * @return
 */
bool T_RegisterCommandCallback(T_Obj *obj, T_Callback callback, void *arg);

/*!
 * @brief Register a callback to receive notifications when a response arrives.
 *
 * @details Setting this callback the Async functions are enabled.
 * The function ::T_Run must be often called to provide processing time to the library.
 *
 * @param obj       Pointer to the object initialized in ::T_Init function.
 * @param callback  Pointer to function to receive the responses.
 * @param arg       Pointer that will used as the first parameter of callback.
 * @return
 */
bool T_RegisterResponseCallback(T_Obj *obj, T_Callback callback, void *arg);

/*!
 * @brief Check for arrived events or async commands
 * 
 * @param[in] obj   Pointer to the object initialized in ::T_Init function.
 * 
 * @return ::Template_Result
 */
bool T_Run (T_Obj *obj);

/*!@}*/

/*! @defgroup CmdAPI Command API
 *  @brief This API is used to implement a Client.
 *  @ingroup API
 *  @{
 */
/*!
 * @brief Used to send the cmd1.
 * 
 * @param[in]   obj   Pointer to the object initialized in ::T_Init function.
 * @param[in]   data  Pointer to the struct to send the data.
 * @param[out]  out   Pointer to the struct to receive the data.
 *    
 * @return ::Template_Result
 */
Template_Result T_Command1(T_Obj *obj, st_cmd1* data, st_cmd1* out);

/*!
 * @brief Used to send the cmd1.
 *
 * @details Does the same as ::T_Command1 however this functions doesn't block until the response
 * arrives. The response will arrive via the callback registered with the function ::T_RegisterResponseCallback
 *
 * @param[in]     obj   Pointer to the object initialized in ::T_Init function.
 * @param[in/out] data  Pointer to the struct to receive the data.
 *
 * @return ::Template_Result
 */
Template_Result T_Command1Async(T_Obj *obj, st_cmd1* data);

/*!
 * @brief Used to send the cmd2.
 * 
 * @param[in]     obj   Pointer to the object initialized in ::T_Init function.
 * @param[in/out] data  Pointer to the struct with the data.
 *
 * @return ::Template_Result
 */
Template_Result T_Command2(T_Obj *obj, st_cmd2* data);


/*!@}*/

/*! @defgroup RespAPI Response API
 * 	@brief This API is used to implement a Server
 *  @ingroup API
 *  @{
 */

/*!
 * @brief Used to send a response to the cmd1.
 *
 * @param[in]  obj   Pointer to the object initialized in ::T_Init function.
 * @param[in]  data  Pointer to the struct to receive the data.
 *
 * @return ::Template_Result
 */
Template_Result T_Response1(T_Obj *obj, Template_Result statusCode, st_cmd1* data);

/*!
 * @brief Used to send a response to the cmd2.
 *
 * @param[in]  obj   Pointer to the object initialized in ::T_Init function.
 * @param[in]  data  Pointer to the struct to receive the data.
 *
 * @return ::Template_Result
 */
Template_Result T_Response2(T_Obj *obj, Template_Result statusCode, st_cmd2* data);


/*!@}*/

/*! @defgroup EvtAPI Event API
 *  @ingroup API
 *  @{
 */

/*!
 * @brief Used to warn.
 *
 * @param[in]  obj   Pointer to the object initialized in ::T_Init function.
 * @param[in]  data  Pointer to the struct with the data.
 *
 * @return ::Template_Result
 */
Template_Result T_Event1(T_Obj *obj, st_cmd1* data);

/*!
 * @brief Used to warn.
 *
 * @param[in]  obj   Pointer to the object initialized in ::T_Init function.
 * @param[in]  data  Pointer to the struct with the data.
 *
 * @return ::Template_Result
 */
Template_Result T_Event2(T_Obj *obj, st_cmd2* data);

/*! @}*/

#endif
