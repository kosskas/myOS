#include <common.h>
#include <boot/gdt.h>
#include <boot/interrupt.h>

//void activate_kb();
//void readCmd();
//char get_char(uint8_t key);

void kernel_main(){
    printf("Hello real world!\n"); 
 
    set_gdt();

    set_idt();
    printf("2. line\n3. line\n4. line\n test");
    //activate_kb();
    ///asm volatile("sti");
    while(1);
        //readCmd();
}
/*
void activate_kb(){
    uint16_t dataport = 0x60;
    uint16_t cmdport = 0x64;
    while(read8(cmdport) & 0x1)
        read8(dataport);
    write8(cmdport,0xAE); // activate interrupts
    write8(cmdport,0x20); // command 0x20 = read controller command byte
    uint8_t status = (read8(dataport) | 1) & ~0x10;
    write8(cmdport,0x60); // command 0x60 = set controller command byte
    write8(dataport,status);
    write8(dataport,0xF4);
}

void readCmd(){
    uint8_t key = read8(0x60);
    char keyc = get_char(key);
    char *buff = "-";
    buff[0] = keyc;
    printf(buff);
}
char get_char(uint8_t key){
    if(key < 0x80) {
        switch (key) {
            case 0x02: return '1';
            case 0x03: return '2';
            case 0x04: return '3';
            case 0x05: return '4';
            case 0x06: return '5';
            case 0x07: return '6';
            case 0x08: return '7';
            case 0x09: return '8';
            case 0x0A: return '9';
            case 0x0B: return '0';

            case 0x10: return 'q';
            case 0x11: return 'w';
            case 0x12: return 'e';
            case 0x13: return 'r';
            case 0x14: return 't';
            case 0x15: return 'z';
            case 0x16: return 'u';
            case 0x17: return 'i';
            case 0x18: return 'o';
            case 0x19: return 'p';

            case 0x1E: return 'a';
            case 0x1F: return 's';
            case 0x20: return 'd';
            case 0x21: return 'f';
            case 0x22: return 'g';
            case 0x23: return 'h';
            case 0x24: return 'j';
            case 0x25: return 'k';
            case 0x26: return 'l';

            case 0x2C: return 'y';
            case 0x2D: return 'x';
            case 0x2E: return 'c';
            case 0x2F: return 'v';
            case 0x30: return 'b';
            case 0x31: return 'n';
            case 0x32: return 'm';
            case 0x33: return ',';
            case 0x34: return '.';
            case 0x35: return '-';

            case 0x1C: return '\n';
            case 0x39: return ' ';
            
            default:
                return key;
        }
    }
    return key;
}
*/