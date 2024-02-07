#include "types.h"

void write(char* str){
    uint16_t* VideoMemory = (uint16_t*)0xB8000;
    for(int i = 0; str[i] != '\0'; i++){
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }
}
void kernel_main(){
    write("first start but with nasm 2");
    while(1);
}