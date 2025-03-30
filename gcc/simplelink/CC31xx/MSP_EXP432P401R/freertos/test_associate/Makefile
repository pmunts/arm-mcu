# Build a SimpleLink WiFi application for the MSP-EXP432P401R using FreeRTOS

ARMSRC		?= $(HOME)/arm-mcu

CC31XXSRC	:= $(ARMSRC)/simplelink/CC31xx
PLATFORM	:= MSP_EXP432P401R
PROJECT		:= $(shell basename $(shell pwd))

CFLAGS		+= -DDEBUG
CFLAGS		+= -DMAX_PAYLOAD_SIZE=256

OBJECTS		+= application.o

default: msp_exp432p401r_default

clean: msp_exp432p401r_clean

include $(CC31XXSRC)/$(PLATFORM)/freertos/common/$(PLATFORM).mk
