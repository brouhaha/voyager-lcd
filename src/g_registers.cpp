// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QGridLayout>
#include <QLabel>
#include <QString>

#include "g_registers.h"

G_Registers::G_Registers(LCD_Registers* lcd_registers,
			 QWidget *parent):
  QWidget(parent),
  lcd_registers(lcd_registers)
{
  QGridLayout *layout = new QGridLayout(this);

  for (int i = 0; i < LCD_Registers::REG_MAX; i++)
  {
    QLabel *label = new QLabel(QString::fromStdString(LCD_Registers::get_register_name(i)));
    hle[i] = new G_Hex_Line_Edit(i, 14, this);

    layout->addWidget(label, i, 0);
    layout->addWidget(hle[i], i, 1);

    connect(hle[i],        &G_Hex_Line_Edit::value_changed,
	    lcd_registers, &LCD_Registers::set_word);
	    
  }

  connect(lcd_registers, &LCD_Registers::word_changed,
	  this,          &G_Registers::lcd_register_word_changed);
}

void G_Registers::lcd_register_word_changed(int register_number, uint64_t old_word, uint64_t new_word)
{
  hle[register_number]->set_value(new_word);
}
