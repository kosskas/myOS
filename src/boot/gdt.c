#include <boot/gdt.h>

__attribute__((aligned(0x10)))
segment_descriptor_t gdt[5];

void create_descriptor(uint32_t num, uint32_t base, uint32_t limit, uint8_t flags) {

    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_high = (base >> 16) & 0xFF;
    gdt[num].base_vhi = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].flags_limit_high = (limit >> 16) & 0x0F;
    gdt[num].flags_limit_high |= 0xC0;
    gdt[num].type = flags;
}
void set_gdt(){
   // printf("Ustawianie deskryptorow\n");
    //???
    create_descriptor(0,0,0,0); //NULL
    create_descriptor(1,0,0xFFFFFFFF,0x9A); //knl Code
    create_descriptor(2,0,0xFFFFFFFF,0x92); //knl data
    create_descriptor(3,0,0xFFFFFFFF,0xFA); //usr code
    create_descriptor(4,0,0xFFFFFFFF,0xF2); //usr data
    ///set gdtr
    uint32_t gdtr[2];
    gdtr[0] = (sizeof(gdt)-1) << 16;
    gdtr[1] = (uint32_t)&gdt;
    //asm volatile("lgdt (%0)": :"p" (((uint8_t *) gdtr)+2));
    load_gdt( ((uint8_t *) gdtr)+2 );
    //printf("GDT zaladowane do gdtr\n");
}