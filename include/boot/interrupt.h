#ifndef _idt_t
#define _idt_t
#include <common.h>
#include <boot/gdt.h>
#include <io/io.h>

struct gate_descriptor{
    uint16_t    handlerAddrLow;
    uint16_t    gdt_codeSegmentSelector;
    uint8_t     reserved;
    uint8_t     access;
    uint16_t    handlerAddrHigh;
} __attribute__((packed));

typedef struct gate_descriptor gate_descriptor_t;

struct idt_ptr{
    uint16_t    size;
    uint32_t    base;
} __attribute__((packed));

typedef struct idt_ptr idt_ptr_t;

void set_idt(gdt_t* gdt, gate_descriptor_t* idt);
void set_idt_entry(gdt_t* gdt, gate_descriptor_t* idt, uint8_t intNum, uint16_t codeSegmentSelectorOffset, void(*intHandler)(), uint8_t descriptorPrivilegeLvl, uint8_t descriptorType);

uint32_t handle_int(uint8_t intNum, uint32_t stackPtr);

void ignore_int_request();
void handle_int_request0x00();
void handle_int_request0x01();

void set_interrupts();
#endif