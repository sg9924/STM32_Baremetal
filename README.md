# STM32_Baremetal
Programming STM32 Microcontrollers with Device Driver libraries built from scratch using basic command line tools and no IDE's.


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
