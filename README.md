# STM32_Baremetal
Programming STM32 Microcontrollers with Device Driver libraries built from scratch using basic command line tools and no IDE's.

_Note: The Driver Files are still in development. They will be updated in the future_

# Board Used:
- Blue Pill: STM32F103C8T6

# Files Structure:
- Device Drivers Header and Source Files
  - Libraries used to interact with hardware
- Startup File
  - startup sequence when the microcontroller is powered on
  - contains,
    - Interrupt / Exception Vector Table
    - Reset Handler
      - transfers the data section into RAM from Flash
      - initializes the bss section (uninitialized variables) with 0
- linker script
  - combines the common sections of various source files into a single one
- make file
  - automating the compilation, linking, creating elf, flashing the microcontroller


# Software Used:
- arm gcc tool chain: https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain
- openocd: https://github.com/xpack-dev-tools/openocd-xpack/releases
- make: https://gnuwin32.sourceforge.net/packages/make.htm
- st-link tools: https://github.com/stlink-org/stlink


# Make Commands:
- `make compile`: Compile the C source files -> Main + Startup + Drivers
- `make dump`: Get a dump of the assembly contents and the section contents of the final code
- `make clean`: Delete the output and dump files created by the compile and dump commands
- `make load`: flash the microcontroller with the final elf generated.
- `make probe`: get info on the microcontroller connected to your system
- `make`: to compile the files and flash the microcontroller all at once
