#ifndef _GDT_H
#define _GDT_H
#include <common.h>
typedef struct segment_descriptor{
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_high;
    uint8_t     type;
    uint8_t     flags_limit_high;
    uint8_t     base_vhi;
} __attribute__((packed)) segment_descriptor_t;

typedef struct gdt_ptr{
    uint16_t    size;
    uint32_t    base;
} __attribute__((packed)) gdt_ptr_t;

void create_descriptor(uint32_t num,uint32_t base, uint32_t limit, uint8_t flags);
void set_gdt();
void load_gdt(gdt_ptr_t* gdtr);
#endif