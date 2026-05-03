#include "../include/vga.h"
#include "../include/keyboard.h"
#include "../include/fs.h"

#define OVERWRITE 0
#define APPEND    1
#define PREPEND   2

void run_editor(char* filename, int mode) {
    clear_screen();

    char buffer[512];
    int index = 0;

    char temp[512];   // for prepend
    int temp_len = 0;

    char* data = get_file_data(filename);

    // ================= MODE HANDLING =================

    // APPEND → load existing content
    if (mode == APPEND && data) {
        int i = 0;
        while (data[i]) {
            buffer[i] = data[i];
            print_char(data[i]);
            i++;
        }
        index = i;
    }

    // PREPEND → store old content separately
    else if (mode == PREPEND && data) {
        int i = 0;
        while (data[i]) {
            temp[i] = data[i];
            i++;
        }
        temp[i] = '\0';
        temp_len = i;
    }

    // OVERWRITE → start fresh

    // ================= CURSOR =================

    print_char('_');

    int cursor_visible = 1;
    int blink_counter = 0;

    // ================= MAIN LOOP =================

    while (1) {

        if (inb(0x64) & 1) {
            unsigned char key = inb(0x60);

            // SHIFT / CAPS
            if (key == 0x2A || key == 0x36) shift_pressed = 1;
            if (key == 0xAA || key == 0xB6) shift_pressed = 0;
            if (key == 0x3A) caps_lock = !caps_lock;

            if (key < 0x80) {

                char c;

                if (shift_pressed) {
                    c = keymap_shift[key];
                } else {
                    c = keymap[key];

                    if (caps_lock && c >= 'a' && c <= 'z') {
                        c -= 32;
                    }
                }

                // remove cursor before typing
                if (cursor_visible) {
                    print_char('\b');
                    cursor_visible = 0;
                }

                // ================= CONTROLS =================

                // ESC → save & exit
                if (key == 1) {

                    // PREPEND: append old data after new
                    if (mode == PREPEND) {
                        int i = 0;
                        while (temp[i]) {
                            buffer[index++] = temp[i];
                            i++;
                        }
                    }

                    buffer[index] = '\0';
                    write_file_data(filename, buffer);
                    return;
                }

                // ENTER
                else if (c == '\n') {
                    if (index < 511) {
                        buffer[index++] = '\n';
                        print_char('\n');
                    }
                }

                // BACKSPACE
                else if (c == '\b') {
                    if (index > 0) {
                        index--;
                        print_char('\b');
                    }
                }

                // NORMAL INPUT
                else if (c) {
                    if (index < 511) {
                        buffer[index++] = c;
                        print_char(c);
                    }
                }
            }
        }

        // ================= BLINKING CURSOR =================

        blink_counter++;

        if (blink_counter > 5000000) {
            blink_counter = 0;

            if (cursor_visible) {
                print_char('\b');
                cursor_visible = 0;
            } else {
                print_char('_');
                cursor_visible = 1;
            }
        }
    }
}
