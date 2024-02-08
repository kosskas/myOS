section .text
    global write8
    global read8
    global write8_slow
    global write16
    global read16
    global write32
    global read32

; Funkcja write8 - zapisuje 8-bitową wartość do portu
write8:
    mov dx, word [esp + 4]  ; Załaduj port do DX
    mov al, byte [esp + 8]  ; Załaduj dane do AL
    out dx, al              ; Zapisz dane do portu
    ret

; Funkcja read8 - odczytuje 8-bitową wartość z portu
read8:
    mov dx, word [esp + 4]  ; Załaduj port do DX
    in al, dx               ; Odczytaj dane z portu
    ret

; Funkcja write8 - zapisuje 8-bitową wartość do portu
write8_slow:
    mov dx, word [esp + 4]  ; Załaduj port do DX
    mov al, byte [esp + 8]  ; Załaduj dane do AL
    out dx, al              ; Zapisz dane do portu
    nop
    nop
    nop
    ret

; Funkcja write16 - zapisuje 16-bitową wartość do portu
write16:
    mov dx, word [esp + 4]  ; Załaduj port do DX
    mov ax, word [esp + 8]  ; Załaduj dane do AX
    out dx, ax              ; Zapisz dane do portu
    ret

; Funkcja read16 - odczytuje 16-bitową wartość z portu
read16:
    mov dx, word [esp + 4]  ; Załaduj port do DX
    in ax, dx               ; Odczytaj dane z portu
    ret

; Funkcja write32 - zapisuje 32-bitową wartość do portu
write32:
    mov dx, word [esp + 4]  ; Załaduj port do DX
    mov eax, dword [esp + 8] ; Załaduj dane do EAX
    out dx, eax             ; Zapisz dane do portu
    ret

; Funkcja read32 - odczytuje 32-bitową wartość z portu
read32:
    mov dx, word [esp + 4]  ; Załaduj port do DX
    in eax, dx              ; Odczytaj dane z portu
    ret
