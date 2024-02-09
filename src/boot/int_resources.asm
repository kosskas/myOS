%define IRQ_BASE 0x20
section .text
extern handle_int

%macro HandleException 1
global handle_int_exception%1
handle_int_exception%1:
    mov byte [intNumber], %1
    jmp int_bottom
%endmacro

%macro HandleInterruptRequest 1
global handle_int_request%1
handle_int_request%1:
    mov byte [intNumber], %1 + IRQ_BASE
    push dword 0
    jmp int_bottom
%endmacro

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:
    push ebp
    push edi
    push esi

    push edx
    push ecx
    push ebx
    push eax

    push esp
    push dword [intNumber]
    call handle_int
    mov esp, eax

    pop eax
    pop ebx
    pop ecx
    pop edx

    pop esi
    pop edi
    pop ebp

    add esp, 4
global ignore_int_request
ignore_int_request:
    iret

section .data
    intNumber db 0