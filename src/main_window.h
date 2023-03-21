// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "lcd.h"
#include "lcd_registers.h"
#include "central_widget.h"

class Main_Window : public QMainWindow
{
    Q_OBJECT

public:
  Main_Window(LCD *lcd,
	      LCD_Registers *lcd_registers);

protected:
  void closeEvent(QCloseEvent *event) override;

private slots:
  void about();

private:
  Central_Widget* central_widget;
};

#endif // MAIN_WINDOW_H
