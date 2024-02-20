#ifndef _CLOCK_H
#define _CLOCK_H
#include <common.h>
#include <io/io.h>
#include <boot/interrupt.h>

void install_clock();
uint32_t clock_handler(uint32_t stackPtr);
void display_time();
#endif