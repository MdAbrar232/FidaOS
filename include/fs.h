#ifndef FS_H
#define FS_H

#include "vga.h"

struct File {
    char name[32];
    void (*program)();
    char data[512];
    int is_program;
};

void add_file(char* name, void (*program)());
void add_text_file(char* name);
void create_file(char* name);
void delete_file(char* name);

void list_files();
void run_file(char* name);

char* get_file_data(char* name);
void write_file_data(char* name, char* data);

#endif
