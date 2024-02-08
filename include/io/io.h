#ifndef _IO_H
#define _IO_H
#include <cmn/types.h>

void write8(uint16_t port, uint8_t data);
uint8_t read8(uint16_t port);

void write8_slow(uint16_t port, uint8_t data);

void write16(uint16_t port, uint16_t data);
uint16_t read16(uint16_t port);

void write32(uint16_t port, uint32_t data);
uint32_t read32(uint16_t port);
#endif