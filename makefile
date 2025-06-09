GCCPARAMS = -m32 -Iinclude -fno-stack-protector -fno-builtin -O2 -Wall
ASPARAMS = -felf32
LDPARAMS = -melf_i386

objects = obj/loader.o \
          obj/kernel_main.o \
          obj/io/io.o \
          obj/boot/gdt.o \
          obj/boot/load_gdt.o \
          obj/boot/load_idt.o \
          obj/boot/interrupt.o \
          obj/boot/int_resources.o \
          obj/cmn/stdio.o \
          obj/cmn/string.o \
          obj/drivers/kb.o \
          obj/drivers/install.o \
          obj/drivers/clock.o

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.asm
	mkdir -p $(@D)
	nasm $(ASPARAMS) -o $@ $<

kernel.bin: linker.ld $(objects)
	mkdir -p bin
	ld $(LDPARAMS) -T $< -o bin/kernel.bin $(objects)

kernel.iso: bin/kernel.bin
	mkdir -p bin/iso
	mkdir -p bin/iso/boot
	mkdir -p bin/iso/boot/grub
	cp bin/kernel.bin bin/iso/boot/kernel.bin
	echo 'set timeout=0' > bin/iso/boot/grub/grub.cfg
	echo 'set default=0' >> bin/iso/boot/grub/grub.cfg
	echo '' >> bin/iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> bin/iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin' >> bin/iso/boot/grub/grub.cfg
	echo '  boot' >> bin/iso/boot/grub/grub.cfg
	echo '}' >> bin/iso/boot/grub/grub.cfg
	grub-mkrescue --output=bin/kernel.iso bin/iso
	rm -rf bin/iso

dis: bin/kernel.bin
	objdump -D -b binary -m i386 --adjust-vma=0x100000 -M intel bin/kernel.bin > bin/dis.txt
.PHONY: clean
clean:
	rm -rf obj bin kernel.iso

.DEFAULT_GOAL := kernel.iso
