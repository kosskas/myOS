#include <io/io.h>

void write8(uint16_t port, uint8_t data){
    __asm__ volatile("outb %0, %1": : "a" (data), "Nd" (port));
}

uint8_t read8(uint16_t port){
    uint8_t ret;
    __asm__ volatile("inb %1, %0": "=a" (ret) : "Nd" (port));
    return ret;
}

void write8_slow(uint16_t port, uint8_t data){
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:": : "a" (data), "Nd" (port));
}

void write16(uint16_t port, uint16_t data){
    __asm__ volatile("outw %0, %1": : "a" (data), "Nd" (port));
}
uint16_t read16(uint16_t port){
    uint16_t ret;
    asm volatile("inw %1, %0": "=a" (ret) : "Nd" (port));
    return ret;
}

void write32(uint16_t port, uint32_t data){
    __asm__ volatile("outl %0, %1": :"a" (data), "Nd" (port));
}
uint32_t read32(uint16_t port){
    uint32_t ret;
    asm volatile("inl %1, %0": "=a" (ret) : "Nd" (port));
    return ret;
}