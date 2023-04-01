// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_REGISTERS_H
#define G_REGISTERS_H

#include <QWidget>

#include "lcd_registers.h"
#include "g_hex_line_edit.h"

class G_Registers: public QWidget
{
public:
  G_Registers(LCD_Registers* lcd_registers,
	      QWidget *parent = nullptr);

private slots:
  void lcd_register_word_changed(int register_number, uint64_t old_word, uint64_t new_word);

private:
  LCD_Registers* lcd_registers;
  G_Hex_Line_Edit *hle[LCD_Registers::REG_MAX];
};

#endif // G_REGISTERS_H
