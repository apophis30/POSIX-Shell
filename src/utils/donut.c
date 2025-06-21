#define _DEFAULT_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int donut() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    printf("\x1b[2J");
    for(;;) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        usleep(30000);
    }
    return 0;
}

// Function to run donut animation for a limited time (for shell startup)
int donut_startup_animation(int frames) {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    
    // Color palette (8 bright colors)
    const char* colors[] = {
        "\033[38;5;196m", // Red
        "\033[38;5;202m", // Orange
        "\033[38;5;226m", // Yellow
        "\033[38;5;46m",  // Green
        "\033[38;5;51m",  // Cyan
        "\033[38;5;21m",  // Blue
        "\033[38;5;93m",  // Purple
        "\033[38;5;201m"  // Pink
    };
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    
    printf("\033[2J\033[H"); // Clear screen and move cursor to top
    
    for(int frame = 0; frame < frames; frame++) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\033[H");
        for(k = 0; k < 1760; k++) {
            if (b[k] != ' ') {
                // Color by character type or position
                int color_index = (b[k] + k) % num_colors;
                printf("%s%c\033[0m", colors[color_index], b[k]);
            } else {
                putchar(' ');
            }
            if ((k + 1) % 80 == 0) putchar('\n');
        }
        A += 0.04;
        B += 0.02;
        usleep(50000); // 50ms per frame
    }
    
    printf("\033[2J\033[H"); // Clear screen after animation
    return 0;
}