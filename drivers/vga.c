#include <stdint.h>

uint16_t* video = (uint16_t*) 0xB8000;
int cursor = 0;

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        video[i] = (0x07 << 8) | ' ';
    }
    cursor = 0;
}

void print_char(char c) {
    if (c == '\n') {
        cursor = (cursor / 80 + 1) * 80;
    }
    else if (c == '\b') {
        if (cursor > 0) {
            cursor--;
            video[cursor] = (0x07 << 8) | ' ';
        }
    }
    else {
        video[cursor++] = (0x07 << 8) | c;
    }
}

void print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        print_char(str[i]);
    }
}
