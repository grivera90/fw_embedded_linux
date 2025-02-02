/**
*******************************************************************************
* @file           : generic_task.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 04/04/2023
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __GENERIC_TASK_H__
#define __GENERIC_TASK_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
/******************************************************************************
        Constants
 ******************************************************************************/

/******************************************************************************
        Data types
 ******************************************************************************/

/******************************************************************************
        Public function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

void generic_task_init(void);
void generic_task_deinit(void);
void generic_task(void *params);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __GENERIC_TASK_H__
