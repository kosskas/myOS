#ifndef _GDT_H
#define _GDT_H
#include <cmn/types.h>

struct segment_descriptor{
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_high;
    uint8_t     type;
    uint8_t     flags_limit_high;
    uint8_t     base_vhi;
} __attribute__((packed));

typedef struct segment_descriptor segment_descriptor_t;

typedef struct GDT {
    segment_descriptor_t nullSegSelector;
    segment_descriptor_t unusedSegSelector;
    segment_descriptor_t codeSegSelector;
    segment_descriptor_t dataSegSelector;
} gdt_t;

void create_descriptor(segment_descriptor_t* segdesc, uint32_t base, uint32_t limit, uint8_t flags);
uint32_t get_base(segment_descriptor_t* segdesc);
uint32_t get_limit(segment_descriptor_t* segdesc);
uint16_t get_dataSegmentDescriptor(gdt_t* gdt);
uint16_t get_codeSegmentDescriptor(gdt_t* gdt);
void set_gdt(gdt_t* gdt);
void load_gdt(void* gdtr_entry);
#endif