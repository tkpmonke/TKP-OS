C_SOURCES = $(wildcard kernel/*.c drivers/*.c drivers/video/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h drivers/video/*.h)
OBJ = $(C_SOURCES:.c=.o)

CFLAGS = -g

CC = i386-elf-gcc
GDB = gdb

image.bin: boot.bin kernel.bin
	cat $^ > image.bin

kernel.bin: kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: image.bin
	qemu-system-i386 -fda image.bin

debug: image.bin kernel.elf
	qemu-system-i386 -s -fda image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: bootloader/%.asm
	nasm $< -f elf -o $@

%.bin: bootloader/%.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
