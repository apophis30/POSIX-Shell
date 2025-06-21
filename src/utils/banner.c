#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_colored_banner() {
    // Clear screen and move cursor to top
    printf("\033[2J\033[H");
    
    // Color codes
    const char* colors[] = {
        "\033[38;5;196m",  // Red
        "\033[38;5;208m",  // Orange
        "\033[38;5;226m",  // Yellow
        "\033[38;5;46m",   // Green
        "\033[38;5;51m",   // Cyan
        "\033[38;5;99m",   // Purple
        "\033[38;5;213m",  // Pink
        "\033[38;5;255m"   // White
    };
    
    const char* reset = "\033[0m";
    const char* bold = "\033[1m";

    // Complete OH MY SHELL Banner
    const char* banner_lines[] = {
        "  ___  _   _   __  __ __   __  ____  _   _ _____ _     _     ",
        " / _ \\| | | | |  \\/  |\\ \\ / / / ___|| | | | ____| |   | |    ",
        "| | | | |_| | | |\\/| | \\ V /  \\___ \\| |_| |  _| | |   | |    ",
        "| |_| |  _  | | |  | |  | |    ___) |  _  | |___| |___| |___ ",
        " \\___/|_| |_| |_|  |_|  |_|   |____/|_| |_|_____|_____|_____|",
        "",
        "Welcome to Oh My Shell! 🐚✨",
        ""
    };
    
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    int color_index = 0;
    
    // Print banner with cycling colors
    for (int i = 0; i < sizeof(banner_lines) / sizeof(banner_lines[0]); i++) {
        if (strlen(banner_lines[i]) > 0) {
            printf("%s%s%s%s\n", colors[color_index], bold, banner_lines[i], reset);
            color_index = (color_index + 1) % num_colors;
        } else {
            printf("\n");
        }
        usleep(50000); // 50ms delay for animation effect
    }
    
    // Print some info
    printf("\033[38;5;51m%sType 'help' for available commands%s\n", bold, reset);
    printf("\033[38;5;46m%sType 'exit' to quit%s\n", bold, reset);
    printf("\033[38;5;208m%sEnjoy your colorful shell experience!%s\n\n", bold, reset);
}

void print_startup_animation() {
    printf("\033[38;5;51m%sStarting Oh My Shell...%s\n", "\033[1m", "\033[0m");
    
    const char* dots[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
    int num_dots = sizeof(dots) / sizeof(dots[0]);
    
    for (int i = 0; i < 20; i++) {
        printf("\r\033[38;5;46m%s Loading %s\033[0m", dots[i % num_dots], "\033[1m");
        fflush(stdout);
        usleep(100000); // 100ms
    }
    printf("\r\033[38;5;46m%s Ready!%s\n\n", "\033[1m", "\033[0m");
} 