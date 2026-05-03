#ifndef VGA_H
#define VGA_H

extern unsigned short* video;
void clear_screen();
void print_char(char c);
void print(const char* str);

#endif
