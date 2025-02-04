AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJ-COPY = arm-none-eabi-objcopy
GDB = arm-none-eabi-gdb
ST-FLASH = st-flash
ST-UTIL  = st-util
RM = rm -rf

.PHONY: all
all: example.elf example.bin

example.elf: example.o
	$(LD) example.o -o example.elf -Ttext=0x08000000

example.o: example.S
	$(AS) example.S -o example.o -gdwarf-2

example.bin: example.elf
	$(OBJ-COPY) -O binary example.elf example.bin


clean:
ifeq ($(OS),Windows_NT)
	@echo "cleaning on Windows"
	-del -fR *.o
	-del -fR *.elf
	-del -fR *.bin
else
	-$(RM) *.o
	-$(RM) *.elf
	-$(RM) *.bin
endif
.PHONY: clean

#See RM0383, section 2.4, Table 3. Memory mapping vs. Boot mode/physical remap in STM32F411xC/E
.PHONY: flash
flash: example.bin
	$(ST-FLASH) write example.bin 0x08000000

.PHONY: gdb-server
gdb-server:
	$(ST-UTIL) -m

.PHONY: gdb
gdb: example.elf
	$(GDB) -tui example.elf -ex "target extended-remote :4242" -ex "load"
