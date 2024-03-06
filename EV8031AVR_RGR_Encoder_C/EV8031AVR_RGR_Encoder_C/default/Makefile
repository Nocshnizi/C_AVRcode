###############################################################################
# Makefile for the project EV8031AVR_RGR_Encoder_C
###############################################################################

## General Flags
PROJECT = EV8031AVR_RGR_Encoder_C
MCU = atmega8515
TARGET = EV8031AVR_RGR_Encoder_C.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=EV8031AVR_RGR_Encoder_C.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = EV8031AVR_RGR_Encoder_C.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) EV8031AVR_RGR_Encoder_C.hex EV8031AVR_RGR_Encoder_C.eep EV8031AVR_RGR_Encoder_C.lss size

## Compile
EV8031AVR_RGR_Encoder_C.o: ../EV8031AVR_RGR_Encoder_C.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) EV8031AVR_RGR_Encoder_C.elf dep/* EV8031AVR_RGR_Encoder_C.hex EV8031AVR_RGR_Encoder_C.eep EV8031AVR_RGR_Encoder_C.lss EV8031AVR_RGR_Encoder_C.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

