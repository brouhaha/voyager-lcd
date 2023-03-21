// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QVBoxLayout>

#include "central_widget.h"

Central_Widget::Central_Widget(LCD* lcd,
			       LCD_Registers *lcd_registers,
			       QWidget* parent,
			       Qt::WindowFlags f) :
  QWidget(parent, f),
  lcd(lcd),
  lcd_registers(lcd_registers),
  g_lcd_view(new G_LCD_View(lcd, this)),
  g_registers(new G_Registers(lcd_registers, this))
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  layout->addWidget(g_lcd_view);
  layout->addWidget(g_registers);

  setLayout(layout);
}
