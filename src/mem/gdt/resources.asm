section .data
gdtr DW 0 ; For limit storage
     DD 0 ; For base storage
section .text
global load_gdt



load_gdt:
    push ebp
    mov ebp, esp
    pushad
    mov eax, [ebp+8]
    mov ebx, [eax]
    mov cx, [eax+4]
    mov [gdtr], cx
    mov [gdtr+2],ebx
    lgdt [gdtr]
    popad
    pop ebp
    ret
