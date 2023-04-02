// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef CENTRAL_WIDGET_H
#define CENTRAL_WIDGET_H

#include <QWidget>

#include "lcd.h"
#include "g_lcd_view.h"
#include "g_registers.h"

class Main_Window;

class Central_Widget : public QWidget
{
public:
  Central_Widget(Main_Window* main_window,
		 LCD* lcd,
		 LCD_Registers* lcd_registers,
		 QWidget* parent = nullptr,
		 Qt::WindowFlags f = Qt::WindowFlags());

private slots:
  

private:
  LCD *lcd;
  LCD_Registers *lcd_registers;
  G_LCD_View* g_lcd_view;
  G_Registers *g_registers;
};

#endif // CENTRAL_WIDGET_H
