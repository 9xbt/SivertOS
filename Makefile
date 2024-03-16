all: build link run

run:
	qemu-system-i386 -drive format=raw,file=bin/SivertOS.bin

build:
	nasm -f bin -o bin/loader.bin src/i386/loader/loader.asm
	nasm -f bin -o bin/kernel.bin src/i386/kernel/kernel.asm

link:
	cat bin/loader.bin bin/kernel.bin > bin/SivertOS.bin

clean:
	- rm -rf bin
	mkdir bin