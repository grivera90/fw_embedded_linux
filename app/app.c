/**
*******************************************************************************
* @file           : app.c
* @brief          : Description of C implementation module
* @author         : Gonzalo Rivera
* @date           : 27/02/2023
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
/******************************************************************************
    Includes
******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "bsp.h"
#include "can_drv.h"
#include "app.h"
#include "scheduler.h"
#define LOG_LOCAL_LEVEL LOG_INFO
#define LOG_CONFIG_TIMESTAMP LOG_TIMESTAMP
#include "log.h"

/* tasks */
#include "blink_task.h"
#include "generic_task.h"
/******************************************************************************
    Defines and constants
******************************************************************************/
#define CAN_PORTS	1
/******************************************************************************
    Data types
******************************************************************************/

/******************************************************************************
    Local variables
******************************************************************************/
static const char *MODULE_NAME = "[APP]";
/******************************************************************************
    Local function prototypes
******************************************************************************/
static void msg_can_update(void *params);
/******************************************************************************
    Local function definitions
******************************************************************************/
static void msg_can_update(void *params)
{
	can_t can = {0};
	uint8_t p = 0;

	for( p = 0; p < CAN_PORTS; p++ )
	{
		/* read all the CAN frames are and pass them up */
		 while(can_rx(p,&can) == 0)
		 {
			LOGI(MODULE_NAME, "msg can rx");
		 }
	}

	return;
}
/******************************************************************************
    Public function definitions
******************************************************************************/
int app_init(void)
{
	int ret = 0;

	/* BSP Init */
	ret = bsp_init();
	
	if(BSP_OK != ret)
	{
		while(1); // handler error TBD.
	}
	
	LOGI(MODULE_NAME,"firmware version: %u.%u.%u", (unsigned int) FW_VER_MAYOR, (unsigned int) FW_VER_MINOR, (unsigned int) FW_VER_PATCH);

	/* others... */

	/* Operative System Init */
	ret = scheduler_init();
	if(SCHEDULER_OK != ret)
	{
		LOGE(MODULE_NAME, "scheduler init error");
	}

	/* Commons Task Init */
	
	/* Add Task's */
	scheduler_add_task(msg_can_update, "msg_can_update", NULL, 0, 10);

	return ret;
}

void app_run(void)
{
	int ret = 0;

	/* Call App Init */
	ret = app_init();

	if(0 != ret)
	{
		while(1); // handler error
	}

	/* Task Init */
	generic_task_init();

	/* Add Task's */
	scheduler_add_task(generic_task, "generic_task", NULL, 0, 20);

	scheduler_start();

	LOGI(MODULE_NAME, "main app initializing...");

	while(true)
	{
		scheduler_dispatch_task();
		YIELD();
	}
}




