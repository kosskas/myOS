GCCPARAMS = -m32 -Iinclude -fno-stack-protector  -fno-builtin
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
	ld $(LDPARAMS) -T $< -o $@ $(objects)

kernel.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp kernel.bin iso/boot/kernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/kernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=kernel.iso iso
	rm -rf iso

.PHONY: clean
clean:
	rm -rf obj kernel.bin kernel.iso
.DEFAULT_GOAL := kernel.iso