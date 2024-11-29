##########################################################################################################################
# NOTE: this file was generated a "huevo"
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
# ------------------------------------------------

######################################
# target
######################################
TARGET = fw_embedded_linux

######################################
# building variables
######################################
# debug build?
#DEBUG = 1
# optimization
#OPT = -Og

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build
BUILD_BIN_DIR = $(BUILD_DIR)/bin
BUILD_OBJ_DIR = $(BUILD_DIR)/obj

######################################
# source
######################################
# C sources
C_SOURCES =  \
main.c \
app/app.c \
app/linux_tasks/blink_task.c \
app/linux_tasks/generic_task.c \
bsp_linux/bsp_linux.c \
bsp_linux/can_drv/can_drv.c \
libraries/cli_board/cli.c \
libraries/configuration_parser/conf_parser.c \
libraries/file_binary_pack/file_binary_pack.c \
libraries/log_debug/log.c \
libraries/ring_buffer/ring_buffer.c \
libraries/scheduler/scheduler.c
#######################################
# compiler
#######################################
CC = gcc
 
#######################################
# CFLAGS
#######################################

# C includes
C_INCLUDES =  \
-Iapp \
-Iapp/linux_tasks \
-Ibsp_linux \
-Ibsp_linux/can_drv \
-Ilibraries/cli_board \
-Ilibraries/configuration_parser \
-Ilibraries/file_binary_pack \
-Ilibraries/log_debug \
-Ilibraries/ring_buffer \
-Ilibraries/scheduler

CFLAGS += -Wall $(C_INCLUDES) -lpthread

# This is for arm i thing that to do delete latter.
#ifeq ($(DEBUG), 1)
#CFLAGS += -g -gdwarf-2
#endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# default action: build all
#all: $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(TARGET) : $(OBJECTS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) -lm

$(BUILD_DIR)/%.o : $(C_SOURCES)/%.c 
	mkdir -p $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) $< -o $@	

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	

$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
	-rm $(TARGET)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***