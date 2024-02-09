#include <common.h>
#include <boot/gdt.h>
#include <boot/interrupt.h>

void kernel_main(){
    printf("Hello real world!\n");
    printf("2. line\n3. line\n4. line");
    gdt_t gdt;
    set_gdt(&gdt);
    gate_descriptor_t idt[256];
    
    set_idt(&gdt, idt);
    //set_interrupts();

    while(1);
}