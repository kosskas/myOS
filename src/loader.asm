BITS 32

section .text
    ALIGN 4
    DD 0x1BADB002
    DD 0x00000000
    DD -(0x1BADB002 + 0x00000000)

global loader
extern kernel_main

loader:
    mov esp, stack_space
    call kernel_main
    hlt
stop:
    cli
    hlt
    jmp stop

section .bss
RESB 8192
stack_space: