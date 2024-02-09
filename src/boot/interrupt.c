#include <boot/interrupt.h>

uint32_t handle_int(uint8_t intNum, uint32_t stackPtr){
    printf(" INTERRUPT!");

    return stackPtr;
}
#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1

void set_idt(gdt_t* gdt, gate_descriptor_t* idt){
    asm("cli");
 
    uint16_t codeSegment = get_codeSegmentSelector(gdt);
    const uint8_t IDT_INTERRUPT_GATE = 0xE;
    for(uint8_t i = 255; i > 0; --i){
        set_idt_entry(&idt[i], codeSegment, &ignore_int_request, 0, IDT_INTERRUPT_GATE);
    }
    
    set_idt_entry(&idt[0x20], codeSegment, &handle_int_request0x00, 0, IDT_INTERRUPT_GATE);
    set_idt_entry(&idt[0x21], codeSegment, &handle_int_request0x01, 0, IDT_INTERRUPT_GATE);
    printf("Przerwania ustawione\n");

    write8_slow(PIC_MASTER_CMD, 0x11);
    write8_slow(PIC_SLAVE_CMD, 0x11);

    write8_slow(PIC_MASTER_DATA, 0x20);
    write8_slow(PIC_SLAVE_DATA, 0x28);

    write8_slow(PIC_MASTER_DATA, 0x04);
    write8_slow(PIC_SLAVE_DATA, 0x02);

    write8_slow(PIC_MASTER_DATA, 0x01);
    write8_slow(PIC_SLAVE_DATA, 0x01);

    write8_slow(PIC_MASTER_DATA, 0x00);
    write8_slow(PIC_SLAVE_DATA, 0x00);
    
    printf("IN/OUT\n");

    idt_ptr_t idtr;
    idtr.size = 256 * sizeof(gate_descriptor_t)-1;
    idtr.base = (uint32_t)idt;
    asm volatile("lidt %0" : : "m" (idtr));
    printf("IDT zaladowane do IDTR\n");
    //asm("sti");

}

void set_idt_entry(gate_descriptor_t* descriptor, uint16_t codeSegmentSelectorOffset, void(*intHandler)(), uint8_t descriptorPrivilegeLvl, uint8_t descriptorType){
    const uint8_t IDT_DESC_PRESENT = 0x80;
    descriptor->handlerAddrLow = ((uint32_t)intHandler & 0xFFFF);
    descriptor->handlerAddrHigh = ((uint32_t)intHandler >> 16);
    descriptor->gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    descriptor->reserved =0;
    descriptor->access = IDT_DESC_PRESENT | descriptorType | ((descriptorPrivilegeLvl & 3) << 5);
}
void set_interrupts(){
    asm("sti");
}