#include <common.h>
#include <boot/gdt.h>
#include <boot/interrupt.h>
#include <drivers/install.h>

void readCmd();
void kernel_main(){
    printf("\nHello world!\n"); 
    set_gdt();
    set_idt();
    install_drivers();
    asm volatile("sti");
    while(1);
       // readCmd();
}


void readCmd(){
    uint8_t key = read8(0x60);
    char keyc = get_char(key);
    char *buff = "?";
    buff[0] = keyc;
    printf(buff);
}