// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>
#include <unordered_map>

#include "lcd_mapper.h"

static std::map<LCD::Segment, LCD_Registers::Bit> normal_segment_to_bit =
{
  // least significant (rightmost) digit
  { LCD::Segment(0, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 53 } },
  { LCD::Segment(0, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 55 } },
  { LCD::Segment(0, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 51 } },
  { LCD::Segment(0, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 41 } },
  { LCD::Segment(0, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 50 } },
  { LCD::Segment(0, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 52 } },
  { LCD::Segment(0, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 54 } },
  { LCD::Segment(0, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 43 } },
  { LCD::Segment(0, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 42 } },

  { LCD::Segment(1, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 47 } },
  { LCD::Segment(1, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 49 } },
  { LCD::Segment(1, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 45 } },
  { LCD::Segment(1, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 33 } },
  { LCD::Segment(1, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 44 } },
  { LCD::Segment(1, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 46 } },
  { LCD::Segment(1, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 48 } },
  { LCD::Segment(1, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 35 } },
  { LCD::Segment(1, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 34 } },

  { LCD::Segment(2, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 29 } },
  { LCD::Segment(2, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 31 } },
  { LCD::Segment(2, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 27 } },
  { LCD::Segment(2, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 39 } },
  { LCD::Segment(2, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 26 } },
  { LCD::Segment(2, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 28 } },
  { LCD::Segment(2, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 30 } },
  { LCD::Segment(2, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 37 } },
  { LCD::Segment(2, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 36 } },

  { LCD::Segment(3, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 21 } },
  { LCD::Segment(3, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 23 } },
  { LCD::Segment(3, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 19 } },
  { LCD::Segment(3, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10,  7 } },
  { LCD::Segment(3, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 18 } },
  { LCD::Segment(3, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 20 } },
  { LCD::Segment(3, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 22 } },
  { LCD::Segment(3, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 25 } },
  { LCD::Segment(3, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 24 } },

  { LCD::Segment(4, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 11 } },
  { LCD::Segment(4, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 13 } },
  { LCD::Segment(4, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10,  9 } },
  { LCD::Segment(4, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 15 } },
  { LCD::Segment(4, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10,  8 } },
  { LCD::Segment(4, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 10 } },
  { LCD::Segment(4, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 12 } },
  { LCD::Segment(4, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 17 } },
  { LCD::Segment(4, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 16 } },

  { LCD::Segment(5, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  43 } },
  { LCD::Segment(5, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  45 } },
  { LCD::Segment(5, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  41 } },
  { LCD::Segment(5, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,   7 } },
  { LCD::Segment(5, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  40 } },
  { LCD::Segment(5, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  42 } },
  { LCD::Segment(5, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  44 } },
  { LCD::Segment(5, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  11 } },
  { LCD::Segment(5, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  10 } },

  { LCD::Segment(6, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  33 } },
  { LCD::Segment(6, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  35 } },
  { LCD::Segment(6, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  31 } },
  { LCD::Segment(6, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,   9 } },
  { LCD::Segment(6, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  30 } },
  { LCD::Segment(6, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  32 } },
  { LCD::Segment(6, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  34 } },
  { LCD::Segment(6, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  37 } },
  { LCD::Segment(6, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  36 } },

  { LCD::Segment(7, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  51 } },
  { LCD::Segment(7, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  53 } },
  { LCD::Segment(7, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  49 } },
  { LCD::Segment(7, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,  13 } },
  { LCD::Segment(7, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  48 } },
  { LCD::Segment(7, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  50 } },
  { LCD::Segment(7, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  52 } },
  { LCD::Segment(7, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  55 } },
  { LCD::Segment(7, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  54 } },

  { LCD::Segment(8, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  27 } },
  { LCD::Segment(8, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  29 } },
  { LCD::Segment(8, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  25 } },
  { LCD::Segment(8, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,  17 } },
  { LCD::Segment(8, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  24 } },
  { LCD::Segment(8, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  26 } },
  { LCD::Segment(8, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  28 } },
  { LCD::Segment(8, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  15 } },
  { LCD::Segment(8, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  14 } },

  { LCD::Segment(9, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  21 } },
  { LCD::Segment(9, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  23 } },
  { LCD::Segment(9, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  19 } },
  { LCD::Segment(9, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,  47 } },
  { LCD::Segment(9, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  18 } },
  { LCD::Segment(9, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  20 } },
  { LCD::Segment(9, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  22 } },
  { LCD::Segment(9, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  39 } },
  { LCD::Segment(9, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  38 } },

  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_NEGATIVE), LCD_Registers::Bit { LCD_Registers::REG_9,  46 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_USER),     LCD_Registers::Bit { LCD_Registers::REG_9,  16 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_F_SHIFT),  LCD_Registers::Bit { LCD_Registers::REG_9,  12 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_G_SHIFT),  LCD_Registers::Bit { LCD_Registers::REG_9,   8 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_BEGIN),    LCD_Registers::Bit { LCD_Registers::REG_9,   6 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_G),        LCD_Registers::Bit { LCD_Registers::REG_10, 14 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_RAD),      LCD_Registers::Bit { LCD_Registers::REG_10,  6 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_D_MY),     LCD_Registers::Bit { LCD_Registers::REG_10, 38 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_C),        LCD_Registers::Bit { LCD_Registers::REG_10, 32 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_PRGM),     LCD_Registers::Bit { LCD_Registers::REG_10, 40 } }
};

static std::map<LCD::Segment, LCD_Registers::Bit> kiss_segment_to_bit =
{
  // least significant (rightmost) digit
  { LCD::Segment(0, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  25 } },
  { LCD::Segment(0, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  23 } },
  { LCD::Segment(0, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  27 } },
  { LCD::Segment(0, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,  19 } },
  { LCD::Segment(0, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  26 } },
  { LCD::Segment(0, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  24 } },
  { LCD::Segment(0, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  22 } },
  { LCD::Segment(0, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  21 } },
  { LCD::Segment(0, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  20 } },

  { LCD::Segment(1, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  31 } },
  { LCD::Segment(1, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  29 } },
  { LCD::Segment(1, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  33 } },
  { LCD::Segment(1, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,  15 } },
  { LCD::Segment(1, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  32 } },
  { LCD::Segment(1, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  30 } },
  { LCD::Segment(1, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  28 } },
  { LCD::Segment(1, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  13 } },
  { LCD::Segment(1, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  12 } },

  { LCD::Segment(2, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  37 } },
  { LCD::Segment(2, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  35 } },
  { LCD::Segment(2, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  39 } },
  { LCD::Segment(2, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,  11 } },
  { LCD::Segment(2, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  38 } },
  { LCD::Segment(2, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  36 } },
  { LCD::Segment(2, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  34 } },
  { LCD::Segment(2, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  17 } },
  { LCD::Segment(2, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  16 } },

  { LCD::Segment(3, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  45 } },
  { LCD::Segment(3, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  43 } },
  { LCD::Segment(3, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  47 } },
  { LCD::Segment(3, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,   9 } },
  { LCD::Segment(3, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  46 } },
  { LCD::Segment(3, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  44 } },
  { LCD::Segment(3, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  42 } },
  { LCD::Segment(3, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  41 } },
  { LCD::Segment(3, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  40 } },

  { LCD::Segment(4, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_9,  53 } },
  { LCD::Segment(4, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_9,  51 } },
  { LCD::Segment(4, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_9,  55 } },
  { LCD::Segment(4, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_9,   7 } },
  { LCD::Segment(4, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_9,  54 } },
  { LCD::Segment(4, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_9,  52 } },
  { LCD::Segment(4, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_9,  50 } },
  { LCD::Segment(4, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_9,  49 } },
  { LCD::Segment(4, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_9,  48 } },

  { LCD::Segment(5, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 37 } },
  { LCD::Segment(5, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 35 } },
  { LCD::Segment(5, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 39 } },
  { LCD::Segment(5, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 21 } },
  { LCD::Segment(5, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 38 } },
  { LCD::Segment(5, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 36 } },
  { LCD::Segment(5, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 34 } },
  { LCD::Segment(5, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 23 } },
  { LCD::Segment(5, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 22 } },

  { LCD::Segment(6, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 29 } },
  { LCD::Segment(6, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 27 } },
  { LCD::Segment(6, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 31 } },
  { LCD::Segment(6, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 19 } },
  { LCD::Segment(6, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 30 } },
  { LCD::Segment(6, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 28 } },
  { LCD::Segment(6, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 26 } },
  { LCD::Segment(6, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 33 } },
  { LCD::Segment(6, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 32 } },

  { LCD::Segment(7, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10,  9 } },
  { LCD::Segment(7, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10,  7 } },
  { LCD::Segment(7, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 11 } },
  { LCD::Segment(7, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 55 } },
  { LCD::Segment(7, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 10 } },
  { LCD::Segment(7, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10,  8 } },
  { LCD::Segment(7, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10,  6 } },
  { LCD::Segment(7, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 25 } },
  { LCD::Segment(7, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 24 } },

  { LCD::Segment(8, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 15 } },
  { LCD::Segment(8, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 13 } },
  { LCD::Segment(8, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 17 } },
  { LCD::Segment(8, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 51 } },
  { LCD::Segment(8, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 16 } },
  { LCD::Segment(8, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 14 } },
  { LCD::Segment(8, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 12 } },
  { LCD::Segment(8, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 53 } },
  { LCD::Segment(8, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 52 } },

  { LCD::Segment(9, LCD::SEG_A),     LCD_Registers::Bit { LCD_Registers::REG_10, 43 } },
  { LCD::Segment(9, LCD::SEG_B),     LCD_Registers::Bit { LCD_Registers::REG_10, 41 } },
  { LCD::Segment(9, LCD::SEG_C),     LCD_Registers::Bit { LCD_Registers::REG_10, 45 } },
  { LCD::Segment(9, LCD::SEG_D),     LCD_Registers::Bit { LCD_Registers::REG_10, 47 } },
  { LCD::Segment(9, LCD::SEG_E),     LCD_Registers::Bit { LCD_Registers::REG_10, 44 } },
  { LCD::Segment(9, LCD::SEG_F),     LCD_Registers::Bit { LCD_Registers::REG_10, 42 } },
  { LCD::Segment(9, LCD::SEG_G),     LCD_Registers::Bit { LCD_Registers::REG_10, 40 } },
  { LCD::Segment(9, LCD::SEG_DOT),   LCD_Registers::Bit { LCD_Registers::REG_10, 49 } },
  { LCD::Segment(9, LCD::SEG_COMMA), LCD_Registers::Bit { LCD_Registers::REG_10, 48 } },

  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_NEGATIVE), LCD_Registers::Bit { LCD_Registers::REG_10, 46 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_USER),     LCD_Registers::Bit { LCD_Registers::REG_10, 50 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_F_SHIFT),  LCD_Registers::Bit { LCD_Registers::REG_10, 54 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_G_SHIFT),  LCD_Registers::Bit { LCD_Registers::REG_10, 18 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_BEGIN),    LCD_Registers::Bit { LCD_Registers::REG_10, 20 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_G),        LCD_Registers::Bit { LCD_Registers::REG_9,   6 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_RAD),      LCD_Registers::Bit { LCD_Registers::REG_9,   8 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_D_MY),     LCD_Registers::Bit { LCD_Registers::REG_9,  10 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_C),        LCD_Registers::Bit { LCD_Registers::REG_9,  14 } },
  { LCD::Segment(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_PRGM),     LCD_Registers::Bit { LCD_Registers::REG_9,  18 } }
};

static std::map<LCD::Segment, LCD_Registers::Bit>* segment_to_bit[LCD_Mapper::MAP_MAX] =
{
  [LCD_Mapper::NORMAL] = & normal_segment_to_bit,
  [LCD_Mapper::KISS]   = & kiss_segment_to_bit
};


static std::map<LCD_Registers::Bit, LCD::Segment> invert_map(const std::map<LCD::Segment, LCD_Registers::Bit>& map)
{
  std::map<LCD_Registers::Bit, LCD::Segment> inv;
  for (auto&[segment, bit]: map)
  {
    if (inv.contains(bit))
    {
      std::cerr << "map inversion error, duplicate value (" << segment << ", " << bit << ")\n";
      std::cerr << "                          prev value (" << inv[bit] << ")\n";
    }
    inv[bit] = segment;
  }
  return inv;
}

static std::map<LCD_Registers::Bit, LCD::Segment> bit_to_segment[LCD_Mapper::MAP_MAX] =
{
  [LCD_Mapper::NORMAL] = invert_map(normal_segment_to_bit),
  [LCD_Mapper::KISS]   = invert_map(kiss_segment_to_bit)
};


LCD_Mapper::LCD_Mapper(LCD* lcd,
		       LCD_Registers* lcd_registers,
		       Map_Type map_type):
  lcd(lcd),
  lcd_registers(lcd_registers),
  map_type(map_type)
{
  connect(lcd,           &LCD::lcd_segment_state_changed,
	  this,          &LCD_Mapper::lcd_segment_state_changed);
  connect(lcd_registers, &LCD_Registers::word_changed,
	  this,          &LCD_Mapper::lcd_register_word_changed);

  connect(this,          &LCD_Mapper::lcd_register_set_bit,
	  lcd_registers, &LCD_Registers::set_bit);
}


void LCD_Mapper::set_map_type(Map_Type new_map_type)
{
  map_type = new_map_type;
  // XXX force resync from segments to register bits
}

void LCD_Mapper::lcd_segment_state_changed(LCD::Segment segment, bool new_state)
{
  if (segment_to_bit[map_type]->contains(segment))
  {
    LCD_Registers::Bit bit = (*segment_to_bit[map_type])[segment];
    emit lcd_register_set_bit(bit.register_number, bit.bit_number, new_state);
  }
  else
  {
    std::cerr << "mapper: no segment to bit mapping found for " << segment << "\n";
  }
}

void LCD_Mapper::lcd_register_word_changed(int register_number, uint64_t old_word, uint64_t new_word)
{
  // std::cout << "mapper: received lcd_register_word_changed(" << register_number << ", " << old_word << ", " << new_word << ")\n";
}
