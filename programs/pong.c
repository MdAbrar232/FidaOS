#include "../include/vga.h"
#include "../include/keyboard.h"

#define DELAY 15000000

void run_pong() {
    clear_screen();

    int paddle_y = 12;
    int ball_x = 40;
    int ball_y = 12;

    int ball_dx = 1;
    int ball_dy = 1;

    // key states
    int move_up = 0;
    int move_down = 0;

    while (1) {

        clear_screen();

        // ================= DRAW PADDLE =================
        for (int i = -2; i <= 2; i++) {
            int pos = (paddle_y + i) * 80 + 2;
            video[pos] = (0x0A << 8) | '|';
        }

        // ================= DRAW BALL =================
        int ball_pos = ball_y * 80 + ball_x;
        video[ball_pos] = (0x0C << 8) | 'O';

        // ================= INPUT =================
        if (inb(0x64) & 1) {
            unsigned char key = inb(0x60);

            // key press
            if (key < 0x80) {
                if (key == 0x11) move_up = 1;   // W
                if (key == 0x1F) move_down = 1; // S
                if (key == 1) return;           // ESC
            }
            // key release
            else {
                key -= 0x80;

                if (key == 0x11) move_up = 0;
                if (key == 0x1F) move_down = 0;
            }
        }

        // ================= MOVE PADDLE =================
        if (move_up) paddle_y--;
        if (move_down) paddle_y++;

        // keep paddle within screen
        if (paddle_y < 2) paddle_y = 2;
        if (paddle_y > 22) paddle_y = 22;

        // ================= MOVE BALL =================
        ball_x += ball_dx;
        ball_y += ball_dy;

        // bounce top/bottom
        if (ball_y <= 0 || ball_y >= 24) {
            ball_dy = -ball_dy;
        }

        // bounce paddle
        if (ball_x == 3 &&
            ball_y >= paddle_y - 2 &&
            ball_y <= paddle_y + 2) {
            ball_dx = -ball_dx;
        }

        // bounce right wall
        if (ball_x >= 79) {
            ball_dx = -ball_dx;
        }

        // ================= GAME OVER =================
        if (ball_x <= 0) {
            clear_screen();
            print("GAME OVER\n");
            return;
        }

        // ================= DELAY =================
        for (int d = 0; d < DELAY; d++);
    }
}
