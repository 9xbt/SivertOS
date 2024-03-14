all:
	make build
	qemu-system-i386 -drive format=raw,file=bin/SivertOS.bin

build:
	nasm -f bin -o bin/entry.bin src/entry.asm
	nasm -f bin -o bin/kernel.bin src/kernel.asm
	cat bin/entry.bin bin/kernel.bin > bin/SivertOS.bin

clean:
	rm -rf bin