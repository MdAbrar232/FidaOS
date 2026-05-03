#include <stdint.h>
#include "../include/vga.h"
#include "../include/keyboard.h"
#include "../include/fs.h"

// external programs
void run_snake();
void run_pong();
void run_editor(char* filename, int mode);

// ================= INPUT =================

char input_buffer[256];
int buffer_index = 0;

// ================= STRING =================

int strcmp(const char* a, const char* b) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}

int strncmp(const char* a, const char* b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return 0;
        if (a[i] == '\0') return 1;
    }
    return 1;
}

// ================= FILE SYSTEM INIT =================

void init_fs() {
    add_file("snake", run_snake);
    add_file("pong", run_pong);
    add_text_file("notes.txt");
}

// ================= KERNEL =================

void trim_newline(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            return;
        }
        i++;
    }
}

void kernel_main() {
    clear_screen();

    init_fs();

    print("Welcome to FidaOS\n");
    print("Type 'help' to see commands\n\n");
    print("FidaOS> ");
    print_char('_');

    int cursor_visible = 1;
    int blink_counter = 0;

    unsigned char key;
    unsigned char last_key = 0;

    while (1) {

        if (inb(0x64) & 1) {

            key = inb(0x60);

            // SHIFT press
            if (key == 0x2A || key == 0x36) shift_pressed = 1;

            // SHIFT release
            if (key == 0xAA || key == 0xB6) shift_pressed = 0;

            // CAPS LOCK toggle
            if (key == 0x3A) caps_lock = !caps_lock;

            if (key < 0x80) {

                if (key != last_key || key == 0x0E) {

                    char c;

                    if (shift_pressed) {
                        c = keymap_shift[key];
                    } else {
                        c = keymap[key];
                        if (caps_lock && c >= 'a' && c <= 'z') {
                            c = c - 32;
                        }
                    }

                    if (c) {

                        // remove cursor before typing
                        if (cursor_visible) {
                            print_char('\b');
                            cursor_visible = 0;
                        }

                        // ENTER
                        if (c == '\n') {
                            print_char('\n');

                            input_buffer[buffer_index] = '\0';
                            trim_newline(input_buffer);

                            if (strcmp(input_buffer, "help")) {
                                print("Commands:\n");
                                print("help  - show commands\n");
                                print("clear - clear screen\n");
                                print("ls    - list files\n");
                                print("run <name> - run program\n");
                                print("cat <file> - view file\n");
				print("touch <file> - create file\n");
				print("edit <file> - overwrite file\n");
				print("append <file> - add to end\n");
				print("prepend <file> - add to beginning\n");
                            }
                            else if (strcmp(input_buffer, "clear")) {
                                clear_screen();
                            }
                            else if (strcmp(input_buffer, "ls")) {
                                list_files();
                            }
			    else if (strncmp(input_buffer, "touch", 5)) {

    				if (input_buffer[5] == '\0') {
        				print("Usage: touch <file>\n");
    				} else {
        				create_file(input_buffer + 6);
    				}
			    }
                            else if (strncmp(input_buffer, "rm", 2)) {

   				if (input_buffer[2] == '\0') {
        				print("Usage: rm <file>\n");
    				} else {
        				delete_file(input_buffer + 3);
    				}
			    }
                            else if (strncmp(input_buffer, "run ", 4)) {
                                run_file(input_buffer + 4);
                            }
                            else if (strncmp(input_buffer, "edit", 4)) {

    if (input_buffer[4] == '\0') {
        print("Usage: edit <file>\n");
    } else {
        run_editor(input_buffer + 5, 0);
    }
}
else if (strncmp(input_buffer, "append", 6)) {

    if (input_buffer[6] == '\0') {
        print("Usage: append <file>\n");
    } else {
        run_editor(input_buffer + 7, 1);
    }
}
else if (strncmp(input_buffer, "prepend", 7)) {

    if (input_buffer[7] == '\0') {
        print("Usage: prepend <file>\n");
    } else {
        run_editor(input_buffer + 8, 2);
    }
}
                            else if (strncmp(input_buffer, "cat", 3)) {

    if (input_buffer[3] == '\0') {
        print("Usage: cat <file>\n");
    } else {
        char* data = get_file_data(input_buffer + 4);

        if (data) {
            print(data);
            print("\n");
        } else {
            print("File not found: ");
            print(input_buffer + 4);
            print("\n");
        }
    }
}
                            else {
                                print("Command not found: ");
				print(input_buffer);
				print("\n");
                            }

                            buffer_index = 0;
                            print("FidaOS> ");
                        }

                        // BACKSPACE
                        else if (c == '\b') {
                            if (buffer_index > 0) {
                                buffer_index--;
                                print_char('\b');
                            }
                        }

                        // NORMAL INPUT
                        else {
                            if (buffer_index < 255) {
                                input_buffer[buffer_index++] = c;
                                print_char(c);
                            }
                        }

                        last_key = key;
                    }
                }
            }
            else {
                last_key = 0;
            }
        }

        // ================= CURSOR BLINK =================

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
