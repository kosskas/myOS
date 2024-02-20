#include <cmn/printf.h>

static uint16_t* VideoMemory = (uint16_t*)0xB8000;
static uint8_t x =0, y =0;

void write(const char* str){
    for(int i = 0; str[i] != '\0'; i++){
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }
}
void printf(const char* str){
    for(int i = 0; str[i] != '\0'; ++i){
        switch (str[i])
        {
        case '\n':
            y++;
            x=0;
            break;
        default:
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
            x++;
            break;
        }
        if(x >= 80){
            y++;
            x=0;
        }
        if(y>=25){
            for(y=0; y<25; y++){
                for(x=0; x<80; x++){
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
                }
            }
            x=0;
            y=0;
        }
    }
}
void display_cursor() {
    static uint8_t flag = 0;
    flag = !flag;

    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | (flag ? '_' : ' ');
}

void return_cursor() {
    if (x == 0 && y == 0)
        return;
    if (x == 0) {
        y--;
        x = 79;
    } else {
        x--;
    }
    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
}