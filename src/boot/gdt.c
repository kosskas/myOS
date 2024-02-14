#include <boot/gdt.h>

void create_descriptor(segment_descriptor_t *descriptor, uint32_t base, uint32_t limit, uint8_t flags) {

    descriptor->base_low = (base & 0xFFFF);
    descriptor->base_high = (base >> 16) & 0xFF;
    descriptor->base_vhi = (base >> 24) & 0xFF;
    descriptor->limit_low = (limit & 0xFFFF);
    descriptor->flags_limit_high = (limit >> 16) & 0x0F;
    descriptor->flags_limit_high |= 0xC0;
    descriptor->type = flags;
}
void set_gdt(){
    //printf("Ustawianie deskryptorow\n");
    //???
    
    static segment_descriptor_t gdt[5] __attribute__((aligned(0x10)));


    create_descriptor(&gdt[0],0,0,0); //NULL
    create_descriptor(&gdt[1],0,0xFFFFFFFF,0x9A); //knl Code
    create_descriptor(&gdt[2],0,0xFFFFFFFF,0x92); //knl data
    create_descriptor(&gdt[3],0,0xFFFFFFFF,0xFA); //usr code
    create_descriptor(&gdt[4],0,0xFFFFFFFF,0xF2); //usr data
    ///set gdtr
    uint32_t gdtr[2];
    gdtr[0] = (sizeof(gdt)-1) << 16;
    gdtr[1] = (uint32_t)&gdt;
    //asm volatile("lgdt (%0)": :"p" (((uint8_t *) gdtr)+2));
    load_gdt( ((uint8_t *) gdtr)+2 );
    //printf("GDT zaladowane do gdtr\n");
    
}
uint16_t get_dataSegmentSelector(segment_descriptor_t* gdt){
    return (uint8_t*)&gdt[2] - (uint8_t*)gdt;
}
uint16_t get_codeSegmentSelector(segment_descriptor_t* gdt){
    return (uint8_t*)&gdt[1] - (uint8_t*)gdt;
    //return (uint8_t*)&gdt->codeSegSelector - (uint8_t*)gdt;
}
uint32_t get_base(segment_descriptor_t* segdesc){
    uint8_t* descriptor = (uint8_t*)segdesc;
    uint32_t ret = descriptor[7];
    ret = (ret << 8)+descriptor[4];
    ret = (ret << 8)+descriptor[3];
    ret = (ret << 8)+descriptor[2];
    return ret;
}
uint32_t get_limit(segment_descriptor_t* segdesc){
    uint8_t* descriptor = (uint8_t*)segdesc;
    uint32_t ret = descriptor[6] & 0xF;
    ret = (ret << 8)+descriptor[1];
    ret = (ret << 8)+descriptor[0];
    
    if((descriptor[6] & 0xC0) == 0xC0)
        ret = (ret << 12) | 0xFFF;
    return ret;
}
