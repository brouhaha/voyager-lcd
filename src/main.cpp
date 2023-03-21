// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QApplication>

#include "lcd.h"
#include "lcd_registers.h"
#include "lcd_mapper.h"
#include "main_window.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  LCD lcd;
  LCD_Registers lcd_registers;
  LCD_Mapper lcd_mapper(&lcd, &lcd_registers);

  Main_Window main_window(&lcd, &lcd_registers);

  main_window.show();
  return app.exec();
}
