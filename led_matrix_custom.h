// led_matrix_custom.h
// Optional custom functions for the LED matrix

#pragma once

#include "esphome.h"

// Helper function to convert x,y coordinates to serpentine LED index
int xy_to_serpentine(int x, int y) {
    // Your layout: bottom-left start, serpentine
    // Row 0 (bottom): left to right
    // Row 1: right to left
    // etc.
    
    if (y < 0 || y >= 8 || x < 0 || x >= 32) {
        return -1; // Out of bounds
    }
    
    int row = 7 - y; // Flip y coordinate (0 is bottom)
    
    if (row % 2 == 0) {
        // Even rows go left to right
        return row * 32 + x;
    } else {
        // Odd rows go right to left
        return row * 32 + (31 - x);
    }
}

// Draw a pixel at x,y coordinates
void draw_pixel(light::AddressableLight *display, int x, int y, Color color) {
    int index = xy_to_serpentine(x, y);
    if (index >= 0 && index < 256) {
        (*display)[index] = color;
    }
}

// Draw a horizontal line
void draw_hline(light::AddressableLight *display, int x, int y, int width, Color color) {
    for (int i = 0; i < width; i++) {
        draw_pixel(display, x + i, y, color);
    }
}

// Draw a vertical line
void draw_vline(light::AddressableLight *display, int x, int y, int height, Color color) {
    for (int i = 0; i < height; i++) {
        draw_pixel(display, x, y + i, color);
    }
}

// Draw a rectangle
void draw_rect(light::AddressableLight *display, int x, int y, int width, int height, Color color, bool filled = false) {
    if (filled) {
        for (int j = 0; j < height; j++) {
            draw_hline(display, x, y + j, width, color);
        }
    } else {
        draw_hline(display, x, y, width, color);
        draw_hline(display, x, y + height - 1, width, color);
        draw_vline(display, x, y, height, color);
        draw_vline(display, x + width - 1, y, height, color);
    }
}

// Simple bitmap font (3x5 pixels for numbers)
const uint8_t FONT_3X5[][5] = {
    {0x7, 0x5, 0x5, 0x5, 0x7}, // 0
    {0x2, 0x6, 0x2, 0x2, 0x7}, // 1
    {0x7, 0x1, 0x7, 0x4, 0x7}, // 2
    {0x7, 0x1, 0x3, 0x1, 0x7}, // 3
    {0x5, 0x5, 0x7, 0x1, 0x1}, // 4
    {0x7, 0x4, 0x7, 0x1, 0x7}, // 5
    {0x7, 0x4, 0x7, 0x5, 0x7}, // 6
    {0x7, 0x1, 0x1, 0x1, 0x1}, // 7
    {0x7, 0x5, 0x7, 0x5, 0x7}, // 8
    {0x7, 0x5, 0x7, 0x1, 0x7}, // 9
};

// Draw a digit
void draw_digit(light::AddressableLight *display, int x, int y, int digit, Color color) {
    if (digit < 0 || digit > 9) return;
    
    for (int row = 0; row < 5; row++) {
        uint8_t line = FONT_3X5[digit][row];
        for (int col = 0; col < 3; col++) {
            if (line & (1 << (2 - col))) {
                draw_pixel(display, x + col, y + row, color);
            }
        }
    }
}

// Draw a number (up to 2 digits)
void draw_number(light::AddressableLight *display, int x, int y, int number, Color color) {
    if (number < 0 || number > 99) return;
    
    if (number >= 10) {
        draw_digit(display, x, y, number / 10, color);
        draw_digit(display, x + 4, y, number % 10, color);
    } else {
        draw_digit(display, x, y, number, color);
    }
}

// Scrolling text buffer structure
struct ScrollBuffer {
    std::vector<uint8_t> buffer;
    int width;
    int position;
    
    ScrollBuffer(int w) : width(w), position(0) {}
    
    void scroll() {
        position++;
        if (position >= width) {
            position = 0;
        }
    }
};