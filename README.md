# Goal
Goal of this project is create simple single-threaded operating system in C/ASM. System should handle hardware interrupts like keyboard or clock. It will have simple shell with few commands and will be running in protected mode with paging.

## Tools
`sudo apt-get install gcc binutils libc6-dev-i386`<br>
`sudo apt-get install nasm`<br>
`sudo apt-get install grub-efi`<br>
`sudo apt-get install mtools`<br>
`sudo apt-get install xorriso`<br>

## Complile
1. Run `make` to build kernel.
2. Run `make kernel.iso` to make iso.
3. Run `make clean` to clean project.

