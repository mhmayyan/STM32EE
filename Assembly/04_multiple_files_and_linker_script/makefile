AS       = arm-none-eabi-as
LD       = arm-none-eabi-ld
OBJ-COPY = arm-none-eabi-objcopy
GDB      = arm-none-eabi-gdb
ST-FLASH = st-flash
ST-UTIL  = st-util

.PHONY: all
all: program.elf program.bin

STM32L4S5VITX_startup.o: STM32L4S5VITX_startup.S
	$(AS) STM32L4S5VITX_startup.S -o STM32L4S5VITX_startup.o -g

main.o: main.S
	$(AS) main.S -o main.o -g

program.elf: STM32L4S5VITX_startup.o main.o STM32L4S5VITX.ld
	$(LD) STM32L4S5VITX_startup.o main.o -o program.elf -T STM32L4S5VITX.ld

program.bin: program.elf
	$(OBJ-COPY) -O binary program.elf program.bin

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.bin

.PHONY: flash
flash: program.bin
	$(ST-FLASH) write program.bin 0x08000000

.PHONY: gdb-server
gdb-server:
	$(ST-UTIL) -m

.PHONY: gdb
gdb: program.elf
	$(GDB) -tui program.elf -ex "target extended-remote :4242" -ex "load"
