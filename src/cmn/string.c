#include <cmn/string.h>

uint32_t strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s);
    return (s - str);
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

void strcpy(char *destination, const char *source) {
    while ((*destination++ = *source++) != '\0');
}

int atoi(const char *str) {
    int result = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        ++str;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        ++str;
    }
    return sign * result;
}

char* itoa(int value, char* str) {
    int base = 10;
    const char* dict = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* ptr = str;
    if (base < 2 || base > 36) {
        *ptr = '\0';
        return str;
    }
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }
    int len = 0;
    int tmp = value;
    do {
        ++len;
        tmp /= base;
    } while (tmp);
    ptr += len;
    *ptr = '\0';
    do {
        *--ptr = dict[value % base];
        value /= base;
    } while (value);
    return str;
}