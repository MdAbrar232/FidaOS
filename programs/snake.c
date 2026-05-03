#include "../include/vga.h"
#include "../include/keyboard.h"

#define DELAY 30000000

void run_snake() {
    clear_screen();

    int snake_x[100];
    int snake_y[100];
    int length = 3;
    int score = 0;

    // initial snake
    snake_x[0] = 40; snake_y[0] = 12;
    snake_x[1] = 39; snake_y[1] = 12;
    snake_x[2] = 38; snake_y[2] = 12;

    int dir = 1;
    int next_dir = 1;

    int food_x = 10;
    int food_y = 5;

    while (1) {

        clear_screen();

        // ================= SCORE =================
        print("Score: ");

        char s[10];
        int temp = score;
        int i = 0;

        if (temp == 0) {
            s[i++] = '0';
        } else {
            while (temp > 0) {
                s[i++] = '0' + (temp % 10);
                temp /= 10;
            }
        }

        // reverse string
        for (int j = 0; j < i / 2; j++) {
            char t = s[j];
            s[j] = s[i - j - 1];
            s[i - j - 1] = t;
        }

        s[i] = '\0';
        print(s);

        // ================= FOOD =================
        int food_pos = food_y * 80 + food_x;
        video[food_pos] = (0x0C << 8) | '*';

        // ================= SNAKE =================
        for (int k = 0; k < length; k++) {
            int pos = snake_y[k] * 80 + snake_x[k];
            video[pos] = (0x0A << 8) | 'O';
        }

        // ================= INPUT =================
        if (inb(0x64) & 1) {
            unsigned char key = inb(0x60);

            if (key < 0x80) {

                if (key == 0x11 && dir != 2) next_dir = 0; // W
                if (key == 0x1F && dir != 0) next_dir = 2; // S
                if (key == 0x1E && dir != 1) next_dir = 3; // A
                if (key == 0x20 && dir != 3) next_dir = 1; // D

                if (key == 1) break; // ESC
            }
        }

        // ================= MOVE BODY =================
        for (int k = length - 1; k > 0; k--) {
            snake_x[k] = snake_x[k - 1];
            snake_y[k] = snake_y[k - 1];
        }

        // apply direction
        dir = next_dir;

        // move head
        if (dir == 0) snake_y[0]--;
        if (dir == 1) snake_x[0]++;
        if (dir == 2) snake_y[0]++;
        if (dir == 3) snake_x[0]--;

        // ================= WRAP =================
        if (snake_x[0] < 0) snake_x[0] = 79;
        if (snake_x[0] >= 80) snake_x[0] = 0;
        if (snake_y[0] < 0) snake_y[0] = 24;
        if (snake_y[0] >= 25) snake_y[0] = 0;

        // ================= COLLISION =================
        for (int k = 1; k < length; k++) {
            if (snake_x[0] == snake_x[k] && snake_y[0] == snake_y[k]) {
                clear_screen();
                print("GAME OVER\n");
                print("Final Score: ");
                print(s);

                for (int d = 0; d < 50000000; d++);
                return;
            }
        }

        // ================= FOOD CHECK =================
        if (snake_x[0] == food_x && snake_y[0] == food_y) {
            length++;
            score++;

            food_x = (food_x + 13) % 80;
            food_y = (food_y + 7) % 25;
        }

        // ================= DELAY =================
        for (int d = 0; d < DELAY; d++);
    }

    clear_screen();
}
