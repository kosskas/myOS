%define IRQ_BASE 0x20
section .text
extern handle_int, handle_int_request0x00, handle_int_request0x01
global ignore_int_request



handle_int_request0x00:
    mov byte [intNumber], 0 + IRQ_BASE
    push dword 0
    jmp int_bottom

handle_int_request0x01:
    mov byte [intNumber], 1 + IRQ_BASE
    push dword 0
    jmp int_bottom

int_bottom:
    pushad
    push ds
    push es
    push fs
    push gs

    push esp
    push dword [intNumber]
    call handle_int  
    add esp, 4
    mov esp, eax
    
    pop gs
    pop fs
    pop es
    pop ds
    popad

ignore_int_request:
    iret

section .data
    intNumber dd 0