/**
*******************************************************************************
* @file           : app.h
* @brief          : Description of header file
* @author         : Gonzalo Rivera
* @date           : 27/02/2023
*******************************************************************************
* @attention
*
* Copyright (c) <date> grivera. All rights reserved.
*
*/
#ifndef __APP_H__
#define __APP_H__
/******************************************************************************
        Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
/******************************************************************************
        Constants
 ******************************************************************************/
#define FW_VER_MAYOR          (1U)
#define FW_VER_MINOR          (0U)
#define FW_VER_PATCH          (0U)
#define FIRMWARE_VERSION      ((FW_VER_MAYOR << 16) | (FW_VER_MINOR << 8) | (FW_VER_PATCH))
/******************************************************************************
        Data types
 ******************************************************************************/

/******************************************************************************
        Public function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

int app_init(void);
void app_run(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // EOF __APP_H__
