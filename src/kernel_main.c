#include <common.h>
#include <boot/gdt.h>

void kernel_main(){
    gdt_t GDT;
    set_gdt(&GDT);
    printf("Hello real world!\n");
    printf("2. line\n3. line\n4. line");
    while(1);
}