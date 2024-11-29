/**
*******************************************************************************
* @file           : generic_task.c
* @brief          : Description of C implementation module
* @author         : Gonzalo Rivera
* @date           : 04/04/2023
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
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include "generic_task.h"
#define LOG_LOCAL_LEVEL LOG_INFO
#define LOG_CONFIG_TIMESTAMP LOG_TIMESTAMP
#include "log.h"
#include "bsp.h"
#include "cli.h"
#include "scheduler.h"
#include "file_binary_pack.h"
/******************************************************************************
    Defines and constants
******************************************************************************/
static const char *TASK_NAME = "[GENERIC_TASK]";

#define ACK 0
#define NACK 1
#define ACCESS_DENIED 2
#define CANNOT_RESPOND 3
#define ERROR -1
#define BOOT_TIMEOUT 20000 // in [ms]
/******************************************************************************
    Data types
******************************************************************************/
typedef enum
{
    APP_RESET_BOOT_MODE = 0,
    APP_RESET,
    APP_ERASE_FLASH,
    APP_ABORT,
    APP_UPGRADE,
    APP_FORCE_UPGRADE
} new_app_code_t;

typedef enum
{
    FSM_STATE_0 = 0,
    FSM_STATE_1,
    FSM_STATE_2,
    FSM_STATE_3,
    FSM_STATE_MAX
} fsm_app_states_t;
/******************************************************************************
    Local variables
******************************************************************************/
static char *ptr = NULL;
static char buffer[512] = {0};
static const char *delim = ":";

static uint8_t fw_upgrade_address = 255;
static uint16_t packets = 0;
static uint16_t packet_count = 0;

static char file_path[50] = {0};
static bool app_force_code = false;
/******************************************************************************
    Local function prototypes
******************************************************************************/
static void set_instance(int argc, char **args);
static void diagnostic(int argc, char **args);
static void force_signal_value(int argc, char **args);
static void fw_upgrade_cmd(int argc, char **args);
/******************************************************************************
    Local function definitions
******************************************************************************/
static void set_instance(int argc, char **args)
{
    uint8_t type = 0;
    uint32_t identity = 0;
    uint32_t identity_end = 0; 
    uint8_t instance = 0;
    uint8_t instance_end = 0;
    
    /* for debug and curiosity only */
    int len = sprintf(buffer, "set_instance type: %s, identity: %s, instance: %s", args[0], args[1], args[2]);
    bsp_write_cmd(buffer, len + 1);
    LOGI(TASK_NAME, "%s", buffer);

    /* a partir de aqui comienza lo bueno */
    type = (uint8_t)atoi(args[0]);

    /* check for identity */
    char *tok = strtok(args[1], delim); 
    if(NULL == tok)
    {
        return;
    }

    identity = (uint32_t)atoi(tok);
    tok = strtok(NULL, delim);
    if(tok != NULL)
    {
        identity_end = (uint32_t)atoi(tok);
    }
    
    /* check for instance */
    tok = strtok(args[2], delim); 
    if(NULL == tok)
    {
        return;
    }

    instance = (uint32_t)atoi(tok);
    tok = strtok(NULL, delim);
    if(tok != NULL)
    {
        instance_end = (uint32_t)atoi(tok);
    }
}

static void diagnostic(int argc, char **args)
{
    uint8_t da = 0; 
    uint32_t spn = 0;
    uint16_t period = 0;
    uint8_t en = 0;

    /* for debug and curiosity only */
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "diag_spn: ");
    for(int i = 0; i < argc; i++)
    {
        strcat(buffer, args[i]);
        if(i < argc - 1)
        {
            strcat(buffer, ",");
        }
    }
    
    bsp_write_cmd(buffer, strlen(buffer) + 1);
    LOGI(TASK_NAME, "%s", buffer);

    /* a partir de aqui comienza lo bueno */
    da = (uint8_t)atoi(args[0]);
    spn = (uint32_t)atoi(args[1]);
    period = (uint16_t)atoi(args[2]);
    en = (!strcmp(args[3], "-e")) ? 1 : 0;
}

static void force_signal_value(int argc, char **args)
{
    uint8_t da = 0; 
    uint32_t spn = 0;
    uint64_t spn_value = 0;
    uint8_t en = 0;

    /* for debug and curiosity only */
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "force_spn: ");
    for(int i = 0; i < argc; i++)
    {
        strcat(buffer, args[i]);
        if(i < argc - 1)
        {
            strcat(buffer, ",");
        }
    }
    
    bsp_write_cmd(buffer, strlen(buffer) + 1);
    LOGI(TASK_NAME, "%s", buffer);

    /* a partir de aqui comienza lo bueno */
    da = (uint8_t)atoi(args[0]);
    spn = (uint32_t)atoi(args[1]);
    spn_value = (uint64_t)atoi(args[2]);
    en = (!strcmp(args[3], "-e")) ? 1 : 0;
}

static void fw_upgrade_cmd(int argc, char **args)
{
    sprintf(file_path, args[0]);

    fw_upgrade_address = (uint8_t)atoi(args[1]);

    LOGI(TASK_NAME, "================      firmware upgrade section      ================");
    LOGI(TASK_NAME, "fw upgrade from: %s", file_path);
    LOGI(TASK_NAME, "to the node address: %d", fw_upgrade_address);
    LOGI(TASK_NAME, "================ read and analize binary file start ================");
    
    load_file(file_path, 1024);
    packets = get_packets();
    packet_count = 0;

    LOGI(TASK_NAME, "bytes: %ld", get_size_in_bytes());
    LOGI(TASK_NAME, "packets: %d | 0x%02X", packets, packets);
    LOGI(TASK_NAME, "sections set: %d", get_chunk_section_set());
    LOGI(TASK_NAME, "================  read and analize binary file end  ================");
}

static void fw_upgrade_force_cmd(int argc, char **args)
{
    fw_upgrade_cmd(argc, &args[0]);
}

static void fw_upgrade_abort_cmd(int argc, char **args)
{
    LOGI(TASK_NAME, "upgrade firmware aborting");
}
/******************************************************************************
    Public function definitions
******************************************************************************/
void generic_task_init(void)
{
    cli_parser_init();
    cli_set_cmd_cb(CMD_SET_INSTANCE, set_instance);
    cli_set_cmd_cb(CMD_DIAGNOSTIC_SPN, diagnostic);
    cli_set_cmd_cb(CMD_FORCE_SPN, force_signal_value);
    cli_set_cmd_cb(CMD_FW_UPGRADE, fw_upgrade_cmd);
    cli_set_cmd_cb(CMD_FW_UPGRADE_FORCE, fw_upgrade_force_cmd);
    cli_set_cmd_cb(CMD_FW_UPGRADE_ABORT, fw_upgrade_abort_cmd);
}

void generic_task_deinit(void)
{

}

void generic_task(void *params)
{
    ptr = bsp_read_cmd();

    if(ptr != NULL && strlen(ptr) > 1)
    {
        cli_parse(ptr);
    }

    bsp_clear_cmd();
}




