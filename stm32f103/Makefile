#Make file for Windows OS
#For Linux some changes need to be made.

#Toolchain Commands
CC=arm-none-eabi-gcc
OBJ=arm-none-eabi-objdump.exe
NM=arm-none-eabi-nm.exe
FLASH=st-flash --reset write
PROBE=st-info --probe

#MCU Params
MACH=cortex-m3           #device
FLASH_ADDR=0x08000000    #flash address where the code needs to be loaded

#Files
LINK=linker.ld           #linker script
MAIN=led_blink           #main file which you want to compile
STARTUP=startup          #startup file
DRIVERS=stm32f103xx_gpio.o stm32f103xx_afio.o stm32f103xx_exti.o stm32f103xx_nvic.o   #driver files

#Flags
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0                #compiler flags: machine, thumb instruction, soft floating, GNU11 C std, show all warnings, no optimizations
DEBUG_FLAG= -g3
LDFLAGS= -mcpu=$(MACH) -mthumb -nostdlib -T $(LINK) -Wl,-Map=logs/final.map           #linker flags: machine, thumb instruction, no std lib, produce a map file


all: compile load                                          #compile and flash the microcontroller
compile: $(MAIN).o $(STARTUP).o $(DRIVERS) final.elf       #compile the source code
stm32f103xx_gpio.o:stm32f103xx_gpio.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_afio.o: stm32f103xx_afio.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_exti.o: stm32f103xx_exti.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_nvic.o: stm32f103xx_nvic.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
$(MAIN).o:$(MAIN).c                                        #compile main source file
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
$(STARTUP).o:$(STARTUP).c                                  #compile startup file
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
final.elf: $(MAIN).o $(DRIVERS) $(STARTUP).o               #create the final executable from main, startup and driver files
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
	
clean:                                                     #Note: This is Windows CMD command to clear the output and dump files. For Linux, the appropriate commands can be substituted here.
	del /s *.o *.elf *.map *.log *.txt *.bin
