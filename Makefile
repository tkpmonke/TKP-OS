C_SOURCES = $(wildcard kernel/*.c drivers/*.c drivers/video/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h drivers/video/*.h)
OBJ = $(C_SOURCES:.c=.o)

CFLAGS = -g

CC = i386-elf-gcc
GDB = gdb

bin/image.bin: bin/boot.bin bin/kernel.bin
	mkdir bin
	cat $^ > $@

bin/kernel.bin: obj/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

bin/debug/kernel.elf: obj/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: bin/image.bin 
	qemu-system-i386 -fda $<

build: bin/tkpos.iso

bin/tkpos.iso: bin/image.bin
	mkdir iso
	dd if=/dev/zero of=bin/floppy.img bs=1024 count=1440
	dd if=$< of=bin/floppy.img seek=0 count=1 conv=notrunc
	genisoimage -quiet -V 'TKP-OS' -input-charset iso8859-1 -o $@ -hide floppy.img iso/

debug: bin/image.bin bin/debug/kernel.elf
	qemu-system-i386 -s -fda bin/image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file bin/debug/kernel.elf"

obj/%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

obj/%.o: bootloader/%.asm
	nasm $< -f elf -o $@

bin/%.bin: bootloader/%.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
