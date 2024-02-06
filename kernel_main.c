
void printf(char* str){
    unsigned short* VideoMemory = (unsigned short*)0xB8000;
    for(int i = 0; str[i] != '\0'; i++){
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }
}
void kernel_main(){
    printf("first start but with nasm");
    while(1);
}