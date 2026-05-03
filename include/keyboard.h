#ifndef KEYBOARD_H
#define KEYBOARD_H

unsigned char inb(unsigned short port);
extern char keymap[128];
extern int shift_pressed;
extern int caps_lock;

extern char keymap[128];
extern char keymap_shift[128];

unsigned char inb(unsigned short port);

#endif
