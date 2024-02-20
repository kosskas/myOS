#ifndef _STRING_H
#define _STRING_H
#include <cmn/types.h>

uint32_t strlen(const char *str);
int strcmp(const char *s1, const char *s2);
int atoi(const char *str);
char* itoa(int value, char* str);
void strcpy(char *destination, const char *source);

#endif