#ifndef _PRINTF_H
#define _PRINTF_H
#include <cmn/types.h>
void write(const char* str, int start);
void printf(const char* str);
void read(char* str);
uint16_t get_last_cursor_pos();
#endif