MEMORY
{
  flash (rx)  : ORIGIN = 0x08000000, LENGTH = 16K
  ram   (xrw) : ORIGIN = 0x20000000, LENGTH = 4K
}

SECTIONS
{
	.text :
	{
		. = ALIGN(4);
		KEEP(*(.interrupt_vector))
		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
		*(.eh_frame)
		KEEP (*(.init))
		KEEP (*(.fini))
		. = ALIGN(4);
		_etext = .;
	} > flash

    .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >flash
    .ARM : {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } >flash

	_data_flash = .;

	.data : AT ( _data_flash )
	{
		. = ALIGN(4);
		_data_begin = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_data_end = .;
	} > ram

	.bss :
	{
		. = ALIGN(4);
		_bss_begin = .;
		__bss_start__ = _bss_begin;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_bss_end = .;
		__bss_end__ = _bss_end;
	} > ram

	_stack_size  = 200;
	_stack_end   = 0x20000000 + 4K; 
	_stack_begin = _stack_end - _stack_size;
	
	. = _stack_begin;
	._stack :
	{
		. = . + _stack_size;
  	} > ram
}

ENTRY(handler_Reset)
