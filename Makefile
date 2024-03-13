all:
	make build
	qemu-system-x86_64 -cdrom kernel.iso

build:
	nasm -f bin -o kernel.bin src/kernel.asm
	mv kernel.bin bin/kernel.bin
	mkisofs -b kernel.bin -no-emul-boot -o kernel.iso bin/
	
clean:
	rm -rvf kernel.bin
	rm -rvf kernel.iso