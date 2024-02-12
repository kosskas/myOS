#include <common.h>
#include <boot/gdt.h>
#include <boot/interrupt.h>

void kernel_main(){
    printf("Hello real world!\n");
    asm("cli");
    printf("2. line\n3. line\n4. line\n");
    gdt_t gdt;
    set_gdt(&gdt);
    __attribute__((aligned(0x10))) 
    static gate_descriptor_t idt[256];
    set_idt(&gdt, idt);
    while(1);
}