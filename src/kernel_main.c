#include <common.h>
#include <boot/gdt.h>
#include <boot/interrupt.h>
#include <drivers/install.h>

void process_start(const char* cmd);

void kernel_main(){
    printf("\nHello world!\n"); 
    set_gdt();
    set_idt();
    install_drivers();
    asm volatile("sti");
    char command[127];
    printf("Avaible commands: time, info\n");
    while(1){
        read(command);
        process_start(command);
    }
}
void process_start(const char* cmd){
    if(strcmp(cmd,"time") == 0){
        while (get_char() != 'x'){
            display_time();
        }
    }
    if(strcmp(cmd,"info") == 0){
        printf("myOS\nMateusz Stencel 2024\n");
    }
}