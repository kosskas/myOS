#include <common.h>
#include <boot/gdt.h>
#include <boot/interrupt.h>

void kernel_main(){
    printf("Hello real world!\n"); 
    asm("cli");
    gdt_t gdt;
    set_gdt(&gdt);
    __attribute__((aligned(0x10))) 
    static gate_descriptor_t idt[256];
    set_idt(&gdt, idt);
    printf("2. line\n3. line\n4. line\n");
    activate_kb();
    asm volatile("sti");
    while(1);
}
void activate_kb(){
    uint16_t dataport = 0x60;
    uint16_t cmdport = 0x64;
    while(read8(cmdport) & 0x1)
        read8(dataport);
    write8(cmdport,0xAE); // activate interrupts
    write8(cmdport,0x20); // command 0x20 = read controller command byte
    uint8_t status = (read8(dataport) | 1) & ~0x10;
    write8(cmdport,0x60); // command 0x60 = set controller command byte
    write8(dataport,status);
    write8(dataport,0xF4);
}