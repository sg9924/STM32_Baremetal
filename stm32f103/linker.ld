ENTRY(Reset_Handler)

MEMORY
{
	FLASH(rx):ORIGIN =0x08000000,LENGTH =128K
	SRAM(rwx):ORIGIN =0x20000000,LENGTH =20K
}

SECTIONS
{
	.text :
	{	
		*(.isr_vector)
		*(.text*)
		_etext = .;
	}> FLASH

	_la_data = LOADADDR(.data);
	.data :
	{	
		_sdata = .;
		*(.data)
		_edata = .;
	}> SRAM AT> FLASH
	
	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	}> SRAM
}