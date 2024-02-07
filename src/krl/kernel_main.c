#include "../cmn/types.h"
#include "../mem/gdt/gdt.h"
void write(char* str){
    uint16_t* VideoMemory = (uint16_t*)0xB8000;
    for(int i = 0; str[i] != '\0'; i++){
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }
}
gdt_t GDT;
void kernel_main(){
    set_gdt(&GDT);
    write("gdt2137");
    while(1);
}