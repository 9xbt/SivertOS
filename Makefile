all:
	make build
	make link
	qemu-system-i386 -drive format=raw,file=bin\SivertOS.bin

build:
	nasm -f bin -o bin/entry.bin src/entry.asm
	nasm -f bin -o bin/kernel.bin src/kernel.asm

link:
ifeq ($(OS), Windows_NT)
	powershell cat bin/entry.bin bin/kernel.bin > bin/SivertOS.bin
else
	cat bin/entry.bin bin/kernel.bin > bin/SivertOS.bin
endif

clean:
ifeq ($(OS), Windows_NT)
	rm -r -fo bin
	mkdir bin
else
	rm -rf bin
endif