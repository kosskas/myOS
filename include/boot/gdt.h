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


void create_descriptor(segment_descriptor_t *descriptor,uint32_t base, uint32_t limit, uint8_t flags);
uint32_t get_base(segment_descriptor_t* segdesc);
uint32_t get_limit(segment_descriptor_t* segdesc);
uint16_t get_dataSegmentSelector(segment_descriptor_t* gdt);
uint16_t get_codeSegmentSelector(segment_descriptor_t* gdt);
void set_gdt();
void load_gdtr(uint16_t limit, uint32_t base);

void load_gdt(void* gdtr);
#endif