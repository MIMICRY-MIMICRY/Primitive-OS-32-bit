# Makefile
CC = x86_64-elf-gcc
AS = nasm
QEMU = qemu-system-i386

CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -std=c99
# Dodano -Wl,-m,elf_i386 aby linker ld.exe wymusił format elf32
LDFLAGS = -m32 -ffreestanding -O2 -nostdlib -Wl,-m,elf_i386 -T linker.ld

OBJS = boot.o kernel.o

all: myos.bin

boot.o: boot.s
	$(AS) -f elf32 boot.s -o boot.o

kernel.o: kernel.c io.h vga.c keyboard.c ata.c
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

# Poprawiona kolejność: obiektowe pliki i LDFLAGS na końcu
myos.bin: $(OBJS) linker.ld
	$(CC) -o myos.bin $(OBJS) $(LDFLAGS)

run: myos.bin
	$(QEMU) -kernel myos.bin

clean:
	rm -f *.o *.bin
