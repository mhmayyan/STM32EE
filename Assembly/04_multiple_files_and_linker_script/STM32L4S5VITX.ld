/*
For FLASH and RAM sizes read RM0432 manual. 2.2.2 Memory map and register boundary addresses, Figure 3. Memory map for STM32L4Rxxx and STM32L4Sxxx

For RAM sizes read RM0432 manual. 2.6.1 Boot configuration, Table 5. Memory mapping versus boot mode/physical remap
*/
MEMORY {
    FLASH   : ORIGIN = 0x08000000, LENGTH = 2048K
    SRAM    : ORIGIN = 0x20000000, LENGTH = 640K
}

SECTIONS {
    .vector_table : {
        *(.vector_table)
    } > FLASH

    .text : {
        *(.text)
    } > FLASH

    .data (NOLOAD) : {
        . = . + 0x400;
        __stack_end = .;
        *(.data)
    } > SRAM
}
