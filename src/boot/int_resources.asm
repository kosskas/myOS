%define IRQ_BASE 0x20
section .text
extern handle_int
global ignore_int_request

%macro handle_int_exception 1
global handle_int_exception%1
handle_int_exception%1:
    mov byte [intNumber], %1 + IRQ_BASE
    push dword 0
    jmp int_bottom
%endmacro

%macro handle_int_request 1
global handle_int_request%1
handle_int_request%1:
    mov byte [intNumber], %1 + IRQ_BASE
    push dword 0
    jmp int_bottom
%endmacro


handle_int_request 0x00
handle_int_request 0x01


int_bottom:
    pushad
    push ds
    push es
    push fs
    push gs

    push esp
    push dword [intNumber]
    call handle_int
    ;add esp, 4
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