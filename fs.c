#include "include/fs.h"
#include "include/vga.h"

#define MAX_FILES 32

struct File files[MAX_FILES];
int file_count = 0;

// ================= STRING COMPARE =================

extern int strcmp(const char* a, const char* b);

// ================= ADD PROGRAM =================

void add_file(char* name, void (*program)()) {
    if (file_count >= MAX_FILES) return;

    int i = 0;
    while (name[i] != '\0') {
        files[file_count].name[i] = name[i];
        i++;
    }
    files[file_count].name[i] = '\0';

    files[file_count].program = program;
    files[file_count].is_program = 1;

    file_count++;
}

// ================= ADD TEXT FILE =================

void add_text_file(char* name) {
    if (file_count >= MAX_FILES) return;

    int i = 0;
    while (name[i] != '\0') {
        files[file_count].name[i] = name[i];
        i++;
    }
    files[file_count].name[i] = '\0';

    files[file_count].is_program = 0;
    files[file_count].data[0] = '\0';

    file_count++;
}

// ================= CREATE FILE =================

void create_file(char* name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name)) {
            print("File already exists\n");
            return;
        }
    }

    add_text_file(name);
    print("File created\n");
}

// ================= DELETE FILE =================

void delete_file(char* name) {
    for (int i = 0; i < file_count; i++) {

        if (strcmp(files[i].name, name)) {

            for (int j = i; j < file_count - 1; j++) {
                files[j] = files[j + 1];
            }

            file_count--;

            print("File deleted\n");
            return;
        }
    }

    print("File not found: ");
    print(name);
    print("\n");
}

// ================= LIST FILES =================

void list_files() {
    for (int i = 0; i < file_count; i++) {

        if (files[i].is_program) {
            print("[PROG] ");
        } else {
            print("[FILE] ");
        }

        print(files[i].name);
        print("\n");
    }
}

// ================= RUN PROGRAM =================

void run_file(char* name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) && files[i].is_program) {
            files[i].program();
            return;
        }
    }

    print("Program not found: ");
    print(name);
    print("\n");
}

// ================= FILE DATA =================

char* get_file_data(char* name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) && !files[i].is_program) {
            return files[i].data;
        }
    }
    return 0;
}

void write_file_data(char* name, char* data) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) && !files[i].is_program) {

            int j = 0;
            while (data[j] != '\0') {
                files[i].data[j] = data[j];
                j++;
            }
            files[i].data[j] = '\0';

            return;
        }
    }
}
