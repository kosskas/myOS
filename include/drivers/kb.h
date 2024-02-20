#ifndef _KB_H
#define _KB_H
#include <common.h>
#include <io/io.h>
#include <boot/interrupt.h>
#define MAX_BUFF_LEN 127
void activate_kb();

uint32_t keyboard_handler(uint32_t stackPtr);

char convert_to_char(uint8_t key);
void get_kbstring(char* dest);
char get_char();
#endif