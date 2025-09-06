// font_5x7_aa.h - 5x7 pixel anti-aliased font for LED Matrix
#pragma once

#include <cmath>

// 5x7 font data - each character is 5 bytes (5 columns x 7 rows)
// Bit 0 is top row, bit 6 is bottom row
const uint8_t font_5x7[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, // 32 space
    {0x00, 0x00, 0x5F, 0x00, 0x00}, // 33 !
    {0x00, 0x07, 0x00, 0x07, 0x00}, // 34 "
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, // 35 #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // 36 $
    {0x23, 0x13, 0x08, 0x64, 0x62}, // 37 %
    {0x36, 0x49, 0x56, 0x20, 0x50}, // 38 &
    {0x00, 0x08, 0x07, 0x03, 0x00}, // 39 '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, // 40 (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, // 41 )
    {0x2A, 0x1C, 0x7F, 0x1C, 0x2A}, // 42 *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, // 43 +
    {0x00, 0x80, 0x70, 0x30, 0x00}, // 44 ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, // 45 -
    {0x00, 0x00, 0x60, 0x60, 0x00}, // 46 .
    {0x20, 0x10, 0x08, 0x04, 0x02}, // 47 /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 48 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 49 1
    {0x72, 0x49, 0x49, 0x49, 0x46}, // 50 2
    {0x21, 0x41, 0x49, 0x4D, 0x33}, // 51 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 52 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 53 5
    {0x3C, 0x4A, 0x49, 0x49, 0x31}, // 54 6
    {0x41, 0x21, 0x11, 0x09, 0x07}, // 55 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 56 8
    {0x46, 0x49, 0x49, 0x29, 0x1E}, // 57 9
    {0x00, 0x00, 0x14, 0x00, 0x00}, // 58 :
    {0x00, 0x40, 0x34, 0x00, 0x00}, // 59 ;
    {0x00, 0x08, 0x14, 0x22, 0x41}, // 60 <
    {0x14, 0x14, 0x14, 0x14, 0x14}, // 61 =
    {0x00, 0x41, 0x22, 0x14, 0x08}, // 62 >
    {0x02, 0x01, 0x59, 0x09, 0x06}, // 63 ?
    {0x3E, 0x41, 0x5D, 0x59, 0x4E}, // 64 @
    {0x7C, 0x12, 0x11, 0x12, 0x7C}, // 65 A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, // 66 B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, // 67 C
    {0x7F, 0x41, 0x41, 0x41, 0x3E}, // 68 D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, // 69 E
    {0x7F, 0x09, 0x09, 0x09, 0x01}, // 70 F
    {0x3E, 0x41, 0x41, 0x51, 0x73}, // 71 G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 72 H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, // 73 I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, // 74 J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, // 75 K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, // 76 L
    {0x7F, 0x02, 0x1C, 0x02, 0x7F}, // 77 M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, // 78 N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 79 O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, // 80 P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, // 81 Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, // 82 R
    {0x26, 0x49, 0x49, 0x49, 0x32}, // 83 S
    {0x03, 0x01, 0x7F, 0x01, 0x03}, // 84 T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, // 85 U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, // 86 V
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, // 87 W
    {0x63, 0x14, 0x08, 0x14, 0x63}, // 88 X
    {0x03, 0x04, 0x78, 0x04, 0x03}, // 89 Y
    {0x61, 0x59, 0x49, 0x4D, 0x43}, // 90 Z
    {0x00, 0x7F, 0x41, 0x41, 0x41}, // 91 [
    {0x02, 0x04, 0x08, 0x10, 0x20}, // 92 backslash
    {0x41, 0x41, 0x41, 0x7F, 0x00}, // 93 ]
    {0x04, 0x02, 0x01, 0x02, 0x04}, // 94 ^
    {0x40, 0x40, 0x40, 0x40, 0x40}, // 95 _
    {0x00, 0x03, 0x07, 0x08, 0x00}, // 96 `
    {0x20, 0x54, 0x54, 0x78, 0x40}, // 97 a
    {0x7F, 0x28, 0x44, 0x44, 0x38}, // 98 b
    {0x38, 0x44, 0x44, 0x44, 0x28}, // 99 c
    {0x38, 0x44, 0x44, 0x28, 0x7F}, // 100 d
    {0x38, 0x54, 0x54, 0x54, 0x18}, // 101 e
    {0x00, 0x08, 0x7E, 0x09, 0x02}, // 102 f
    {0x18, 0xA4, 0xA4, 0x9C, 0x78}, // 103 g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, // 104 h
    {0x00, 0x44, 0x7D, 0x40, 0x00}, // 105 i
    {0x20, 0x40, 0x40, 0x3D, 0x00}, // 106 j
    {0x7F, 0x10, 0x28, 0x44, 0x00}, // 107 k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, // 108 l
    {0x7C, 0x04, 0x78, 0x04, 0x78}, // 109 m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, // 110 n
    {0x38, 0x44, 0x44, 0x44, 0x38}, // 111 o
    {0xFC, 0x18, 0x24, 0x24, 0x18}, // 112 p
    {0x18, 0x24, 0x24, 0x18, 0xFC}, // 113 q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, // 114 r
    {0x48, 0x54, 0x54, 0x54, 0x24}, // 115 s
    {0x04, 0x04, 0x3F, 0x44, 0x24}, // 116 t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, // 117 u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, // 118 v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, // 119 w
    {0x44, 0x28, 0x10, 0x28, 0x44}, // 120 x
    {0x4C, 0x90, 0x90, 0x90, 0x7C}, // 121 y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, // 122 z
    {0x00, 0x08, 0x36, 0x41, 0x00}, // 123 {
    {0x00, 0x00, 0x77, 0x00, 0x00}, // 124 |
    {0x00, 0x41, 0x36, 0x08, 0x00}, // 125 }
    {0x02, 0x01, 0x02, 0x04, 0x02}, // 126 ~
};

// Helper function to draw a character at position
void draw_char(light::AddressableLight &it, char c, int x_pos, int y_pos, Color color) {
    if (c < 32 || c > 126) return;  // Character out of range
    
    const uint8_t *char_data = font_5x7[c - 32];
    
    for (int col = 0; col < 5; col++) {
        int x = x_pos + col;
        if (x < 0 || x >= 32) continue;  // Skip if out of bounds
        
        uint8_t column = char_data[col];
        for (int row = 0; row < 7; row++) {
            if (column & (1 << row)) {
                int y = y_pos + row;
                if (y < 0 || y >= 8) continue;  // Skip if out of bounds
                
                // Convert to LED index with serpentine mapping
                int flipped_y = 7 - y;
                int led_index;
                if (flipped_y % 2 == 0) {
                    led_index = flipped_y * 32 + x;
                } else {
                    led_index = flipped_y * 32 + (31 - x);
                }
                
                if (led_index >= 0 && led_index < 256) {
                    it[led_index] = color;
                }
            }
        }
    }
}

// Helper function to draw a string
void draw_string(light::AddressableLight &it, const std::string &text, int x_pos, int y_pos, Color color) {
    int current_x = x_pos;
    
    for (size_t i = 0; i < text.length(); i++) {
        draw_char(it, text[i], current_x, y_pos, color);
        current_x += 6;  // 5 pixels for char + 1 pixel spacing
    }
}

// Calculate text width in pixels
int get_text_width(const std::string &text) {
    return text.length() * 6 - 1;  // 6 pixels per char minus 1 for last spacing
}


// Anti-aliased drawing with sub-pixel positioning
void draw_char_aa(light::AddressableLight &it, char c, float x_pos, float y_pos, Color color, float brightness = 1.0) {
    if (c < 32 || c > 126) return;
    
    const uint8_t *char_data = font_5x7[c - 32];
    
    // Calculate fractional offsets
    int x_start = (int)floor(x_pos);
    int y_start = (int)floor(y_pos);
    float x_frac = x_pos - x_start;
    float y_frac = y_pos - y_start;
    
    // Draw with 2x2 supersampling for anti-aliasing
    for (int col = 0; col < 5; col++) {
        uint8_t column = char_data[col];
        
        for (int row = 0; row < 7; row++) {
            if (column & (1 << row)) {
                // Calculate anti-aliased pixel coverage for 4 affected pixels
                float coverage[2][2] = {
                    {(1.0f - x_frac) * (1.0f - y_frac), x_frac * (1.0f - y_frac)},
                    {(1.0f - x_frac) * y_frac, x_frac * y_frac}
                };
                
                // Draw to up to 4 pixels with appropriate brightness
                for (int dy = 0; dy < 2; dy++) {
                    for (int dx = 0; dx < 2; dx++) {
                        int x = x_start + col + dx;
                        int y = y_start + row + dy;
                        
                        if (x >= 0 && x < 32 && y >= 0 && y < 8) {
                            // Convert to LED index
                            int flipped_y = 7 - y;
                            int led_index;
                            if (flipped_y % 2 == 0) {
                                led_index = flipped_y * 32 + x;
                            } else {
                                led_index = flipped_y * 32 + (31 - x);
                            }
                            
                            if (led_index >= 0 && led_index < 256) {
                                // Apply anti-aliased brightness
                                float pixel_brightness = coverage[dy][dx] * brightness;
                                
                                // Blend with existing pixel
                                Color existing = it[led_index].get();
                                Color new_color(
                                    existing.r + (color.r - existing.r) * pixel_brightness,
                                    existing.g + (color.g - existing.g) * pixel_brightness,
                                    existing.b + (color.b - existing.b) * pixel_brightness
                                );
                                it[led_index] = new_color;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Helper for edge smoothing using 3x3 kernel
void apply_edge_smoothing(light::AddressableLight &it, int x, int y, Color color, float strength) {
    // 3x3 Gaussian kernel for smoothing
    const float kernel[3][3] = {
        {0.075f, 0.124f, 0.075f},
        {0.124f, 0.204f, 0.124f},
        {0.075f, 0.124f, 0.075f}
    };
    
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int px = x + dx;
            int py = y + dy;
            
            if (px >= 0 && px < 32 && py >= 0 && py < 8) {
                int flipped_y = 7 - py;
                int led_index;
                if (flipped_y % 2 == 0) {
                    led_index = flipped_y * 32 + px;
                } else {
                    led_index = flipped_y * 32 + (31 - px);
                }
                
                if (led_index >= 0 && led_index < 256) {
                    float weight = kernel[dy + 1][dx + 1] * strength;
                    Color existing = it[led_index].get();
                    Color new_color(
                        existing.r + (color.r - existing.r) * weight,
                        existing.g + (color.g - existing.g) * weight,
                        existing.b + (color.b - existing.b) * weight
                    );
                    it[led_index] = new_color;
                }
            }
        }
    }
}

// Improved string drawing with anti-aliasing
void draw_string_aa(light::AddressableLight &it, const std::string &text, float x_pos, float y_pos, Color color) {
    float current_x = x_pos;
    
    for (size_t i = 0; i < text.length(); i++) {
        draw_char_aa(it, text[i], current_x, y_pos, color);
        current_x += 6.0f;  // Can use fractional spacing
    }
}

// Alternative: Pre-rendered anti-aliased font (2-bit per pixel)
// This would store 4 brightness levels per pixel for better quality
struct AAGlyph {
    uint8_t width;
    uint8_t height;
    uint8_t data[35];  // 5x7 pixels, 2 bits each = 70 bits = ~9 bytes
};

// Function to render with pre-computed anti-aliased glyphs
void draw_aa_glyph(light::AddressableLight &it, const AAGlyph &glyph, int x, int y, Color color) {
    for (int row = 0; row < glyph.height; row++) {
        for (int col = 0; col < glyph.width; col++) {
            // Extract 2-bit brightness value (0, 85, 170, 255)
            int bit_index = (row * glyph.width + col) * 2;
            int byte_index = bit_index / 8;
            int bit_offset = bit_index % 8;
            
            uint8_t brightness_bits = (glyph.data[byte_index] >> bit_offset) & 0x03;
            float brightness = brightness_bits / 3.0f;
            
            if (brightness > 0) {
                int px = x + col;
                int py = y + row;
                
                if (px >= 0 && px < 32 && py >= 0 && py < 8) {
                    int flipped_y = 7 - py;
                    int led_index;
                    if (flipped_y % 2 == 0) {
                        led_index = flipped_y * 32 + px;
                    } else {
                        led_index = flipped_y * 32 + (31 - px);
                    }
                    
                    if (led_index >= 0 && led_index < 256) {
                        it[led_index] = Color(
                            color.r * brightness,
                            color.g * brightness,
                            color.b * brightness
                        );
                    }
                }
            }
        }
    }
}