#include <boot/gdt.h>

void create_descriptor(segment_descriptor_t* segdesc, uint32_t base, uint32_t limit, uint8_t flags) {
    //distribute data over structure byte per byte
    uint8_t* descriptor = (uint8_t)segdesc;

    if(limit < 0xFFFF){
        descriptor[6]=0x40;
    }
    else{
        if((limit & 0xFFF) != 0xFFF)
            limit = (limit >>12)-1;
        else
            limit = limit >>12;
        descriptor[6] = 0xC0;
    }
    //set limit
    descriptor[0] = limit & 0xFF;
    descriptor[1] = (limit>>8) & 0xFF;
    descriptor[6] |= (limit>>16) & 0xF;

    //set base
    descriptor[2] = base & 0xFF;
    descriptor[3] = (base>>8) & 0xFF;
    descriptor[4] = (base>>16) & 0xFF;
    descriptor[7] = (base>>24) & 0xFF;

    //set flags
    descriptor[5] = flags;
}
void set_gdt(gdt_t* gdt){
    create_descriptor(&gdt->nullSegSelector, 0,0,0);
    create_descriptor(&gdt->unusedSegSelector, 0,0,0);
    create_descriptor(&gdt->codeSegSelector, 0,0x04000000,0x9A); //64*1024*1024
    create_descriptor(&gdt->dataSegSelector, 0,0x04000000,0x92);
    ///set gdtr
    uint32_t gdtr[2];
    gdtr[0] = (uint32_t)gdt;
    gdtr[1] = sizeof(gdt) <<16;
    asm volatile("lgdt (%0)": :"p" (((uint8_t *) gdtr)+2));
    printf("GDT zaladowane do gdtr\n");
    
}
uint16_t get_dataSegmentSelector(gdt_t* gdt){
    return (uint8_t*)&gdt->dataSegSelector - (uint8_t*)gdt;
}
uint16_t get_codeSegmentSelector(gdt_t* gdt){
    return (uint8_t*)&gdt->codeSegSelector - (uint8_t*)gdt;
}
uint32_t get_base(segment_descriptor_t* segdesc){
    uint8_t* descriptor = (uint8_t)segdesc;
    uint32_t ret = descriptor[7];
    ret = (ret << 8)+descriptor[4];
    ret = (ret << 8)+descriptor[3];
    ret = (ret << 8)+descriptor[2];
    return ret;
}
uint32_t get_limit(segment_descriptor_t* segdesc){
    uint8_t* descriptor = (uint8_t)segdesc;
    uint32_t ret = descriptor[6] & 0xF;
    ret = (ret << 8)+descriptor[1];
    ret = (ret << 8)+descriptor[0];
    
    if((descriptor[6] & 0xC0) == 0xC0)
        ret = (ret << 12) | 0xFFF;
    return ret;
}
