#include <drivers/clock.h>

uint8_t ticks = 0;
uint64_t secs = 0;

void install_clock(){
    install_handler(0x20, clock_handler);
}
uint32_t clock_handler(uint32_t stackPtr){
    ticks++;
    if(ticks >= 20){
        //printf("*");
        ticks = 0;
        secs++;
        //display_time();    
    }
    
    return stackPtr;
}
void display_time(){
    char buff[20] = "Time ";
    itoa(secs, buff+5);
    write(buff,get_last_cursor_pos());
}