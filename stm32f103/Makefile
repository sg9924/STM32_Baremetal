#Make file for Windows OS
#For Linux some changes need to be made.

#Toolchain Commands
CC=arm-none-eabi-gcc
OBJ_DUMP=arm-none-eabi-objdump.exe
OBJ_COPY=arm-none-eabi-objcopy
NM=arm-none-eabi-nm.exe
GDB=arm-none-eabi-gdb.exe
FLASH=st-flash --reset write
PROBE=st-info --probe

#Toolchain Paths
OPENOCD_DIR={YOUR_DIR}\xpack-openocd-0.12.0-3\openocd

#Openocd
#Configuration File
#Interface
OPENOCD_INTF_CFG_FILE=$(OPENOCD_DIR)\scripts\interface\stlink-v2.cfg
#target
OPENOCD_TGT_CFG_FILE=$(OPENOCD_DIR)\scripts\target\stm32f1x.cfg

#MCU Params
MACH=cortex-m3           #device
FLASH_ADDR=0x08000000    #flash address where the code needs to be loaded

#Directories
WORK_DIR={YOUR_WORK_DIR}
OBJ_DIR=Objects
INC_DIR=Inc
SRC_DIR=Src

#Files
LINK=linker.ld           #linker script
MAIN=led_blink           #main file which you want to compile
STARTUP=startup          #startup file
DRIVERS=stm32f103xx_gpio.o stm32f103xx_afio.o stm32f103xx_exti.o stm32f103xx_nvic.o \
        stm32f103xx_usart.o stm32f103xx_rcc.o stm32f103xx_spi.o stm32f103xx_adc.o   \
		stm32f103xx_i2c.o stm32f103xx_timer.o stm32f103xx_dma.o stm32f103xx_systick.o          #driver files
OTHERS=stm32f103xx_init.o stm32f103xx_serial.o stm32f103xx_utilities.o
MIDDLEWARE=lcd_16x2.o

#Flags
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0                         #compiler flags: machine, thumb instruction, soft floating, GNU11 C std, show all warnings, no optimizations
DEBUG_FLAG= -g3
LDFLAGS= --specs=nano.specs -mcpu=$(MACH) -mthumb -T $(LINK) -Wl,-Map=logs/final.map           #linker flags: machine, thumb instruction, with std lib (nano specs), produce a map file


all: compile load                                          #compile and flash the microcontroller
compile: clean final.elf clean-obj                         #compile the source code
stm32f103xx_gpio.o:stm32f103xx_gpio.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_afio.o: stm32f103xx_afio.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_exti.o: stm32f103xx_exti.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_nvic.o: stm32f103xx_nvic.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_usart.o: stm32f103xx_usart.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_rcc.o: stm32f103xx_rcc.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_spi.o: stm32f103xx_spi.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_adc.o: stm32f103xx_adc.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_i2c.o: stm32f103xx_i2c.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_timer.o: stm32f103xx_timer.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_dma.o: stm32f103xx_dma.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_init.o: stm32f103xx_init.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_serial.o: stm32f103xx_serial.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_systick.o: stm32f103xx_systick.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_utilities.o: stm32f103xx_utilities.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
$(MAIN).o:$(MAIN).c                                        #compile main source file
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
$(STARTUP).o:$(STARTUP).c                                  #compile startup file
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
$(SYSCALLS).o:$(SYSCALLS).c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
final.elf: $(MAIN).o $(DRIVERS) $(OTHERS) $(MIDDLEWARE) $(STARTUP).o $(SYSCALLS).o               #create the final executable from main, startup and driver files
	$(CC) $(LDFLAGS) $^ -o $@

final.bin:final.elf                                        #convert the executable from elf to binary to flash the MCU
	arm-none-eabi-objcopy -O binary $^ $@
load:final.bin                                             #flash the executable into the MCU with st-tools utility
	$(FLASH) $^ $(FLASH_ADDR)

examine-sections:
	$(OBJ) -h final.elf
examine-symbols:
	$(NM) final.elf
dump:$(MAIN).o
	$(OBJ) -d $^ > logs/assembly_dump.txt
	$(OBJ) -h $^ > logs/section_contents.txt
	$(OBJ) -s $^ > logs/section_contents_detailed.txt
	$(NM) final.elf > logs/symbols.txt
probe:
	$(PROBE)


debug: openocd gdb
openocd:
	openocd -f $(OPENOCD_INTF_CFG_FILE) -f $(OPENOCD_TGT_CFG_FILE)
gdb:
	$(GDB) final.elf

.PHONY: clean clean-obj
clean:                                                     #Note: This is Windows CMD command to clear the output and dump files. For Linux, the appropriate commands can be substituted here.
	del /s *.o *.elf *.map *.log *.txt *.bin
clean-obj:
	del /s *.o
