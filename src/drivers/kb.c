#include <drivers/kb.h>

char scancodeToAscii [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

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

    install_handler(0x21, keyboard_handler);
}

uint32_t keyboard_handler(uint32_t stackPtr){
    uint8_t key = read8(0x60);
    if(key < 0x80) {
        char* text = " ";   
        text[0] = get_char(key);
        printf(text);
    }
    return stackPtr;
}
char get_char(uint8_t key){
    if(key < 0x80) {
        return scancodeToAscii[key];
    }
    return '?';
}