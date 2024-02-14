section .text
global load_gdt

load_gdt:
    mov eax, [esp+4]
    lgdt [eax]

    mov eax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x8:set_cs
set_cs:
    ret