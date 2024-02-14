#ifndef _KB_H
#define _KB_H
#include <common.h>
#include <io/io.h>
#include <boot/interrupt.h>

void activate_kb();

uint32_t keyboard_handler(uint32_t stackPtr);

char get_char(uint8_t key);
#endif