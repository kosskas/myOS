#include <common.h>
#include <boot/gdt.h>
#include <boot/interrupt.h>
#include <drivers/kb.h>

void readCmd();
int sprawdz();
void kernel_main(){
    printf("Hello real world!\n"); 
    set_gdt();
    set_idt();
    printf("2. line\n3. line\n4. line\n test");
    activate_kb();
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