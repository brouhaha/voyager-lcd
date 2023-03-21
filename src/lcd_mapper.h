// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef LCD_MAPPER_H
#define LCD_MAPPER_H

#include <QObject>

#include "lcd.h"
#include "lcd_registers.h"

class LCD_Mapper: public QObject
{
  Q_OBJECT

public:

  enum Map_Type { NORMAL, KISS, MAP_MAX };

  LCD_Mapper(LCD* lcd,
	     LCD_Registers* lcd_registers,
	     Map_Type map_type = NORMAL);

  void set_map_type(Map_Type new_map_type);

private slots:
  // From LCD:
  void lcd_segment_state_changed(LCD::Segment segment, bool new_state);

  // From LCD_Register:
  void lcd_register_word_changed(int register_number, uint64_t old_word, uint64_t new_word);

signals:
  // To LCD:
  void set_segment(LCD::Segment segment, bool new_state);

  // To LCD_Register:
  void lcd_register_set_bit(int register_number, int bit_number, bool new_bit);

private:
  LCD* lcd;
  LCD_Registers* lcd_registers;
  Map_Type map_type;
};

#endif // LCD_MAPPER_H

