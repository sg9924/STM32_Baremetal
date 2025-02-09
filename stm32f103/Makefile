#CMD Commands
CC=arm-none-eabi-gcc
OBJ=arm-none-eabi-objdump.exe
NM=arm-none-eabi-nm.exe
FLASH=st-flash --reset write
PROBE=st-info --probe

#MCU Params
MACH=cortex-m3
FLASH_ADDR=0x08000000

#Files
LINK=bp_linker.ld
MAIN=bp_led_blink
STARTUP=bp_startup
DRIVERS=stm32f103xx_gpio.o stm32f103xx_afio.o stm32f103xx_exti.o stm32f103xx_nvic.o

#Flags
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
DEBUG_FLAG= -g3
LDFLAGS= -mcpu=$(MACH) -mthumb -nostdlib -T $(LINK) -Wl,-Map=logs/final.map


all: compile load
compile: $(MAIN).o $(STARTUP).o $(DRIVERS) final.elf
stm32f103xx_gpio_driver.o:stm32f103xx_gpio.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_afio_driver.o: stm32f103xx_afio.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_exti_driver.o: stm32f103xx_exti.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
stm32f103xx_nvic.o: stm32f103xx_nvic.c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
$(MAIN).o:$(MAIN).c 
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
$(STARTUP).o:$(STARTUP).c
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $^ -o $@
final.elf: $(MAIN).o $(DRIVERS) $(STARTUP).o
	$(CC) $(LDFLAGS) $^ -o $@

final.bin:final.elf
	arm-none-eabi-objcopy -O binary $^ $@
load:final.bin
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
	
clean:
	del /s *.o *.elf *.map *.log *.txt *.bin