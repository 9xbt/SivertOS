all: build link run

run:
	qemu-system-i386 -drive format=raw,file=bin/SivertOS.bin

build:
	mkdir -p bin/bootloader
	nasm -f bin -o bin/bootloader/stage1.bin src/arch/i386/bootloader/stage1.asm
	nasm -f bin -o bin/bootloader/stage2.bin src/arch/i386/bootloader/stage2.asm

link:
	cat bin/bootloader/stage1.bin bin/bootloader/stage2.bin > bin/SivertOS.bin

clean:
	rm -rf bin