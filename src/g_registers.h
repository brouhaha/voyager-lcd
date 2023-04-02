// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_REGISTERS_H
#define G_REGISTERS_H

#include <QWidget>

#include "main_window.h"
#include "lcd_registers.h"
#include "g_hex_line_edit.h"
#include "g_user_code.h"

class G_Registers: public QWidget
{
public:
  G_Registers(Main_Window* main_window,
	      LCD_Registers* lcd_registers,
	      QWidget *parent = nullptr);

public slots:
  void view_user_code(bool enable);

private slots:
  void lcd_register_word_changed(int register_number, uint64_t old_word, uint64_t new_word);

private:
  LCD_Registers* lcd_registers;
  G_Hex_Line_Edit *hle[LCD_Registers::REG_MAX];
  G_User_Code *uc[LCD_Registers::REG_MAX];
};

#endif // G_REGISTERS_H
