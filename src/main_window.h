// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "lcd.h"
#include "lcd_registers.h"

class Central_Widget;

class Main_Window : public QMainWindow
{
    Q_OBJECT

public:
  Main_Window(LCD* lcd,
	      LCD_Registers* lcd_registers);

signals:
  void view_user_code(bool enable);

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void about();

  void cut();
  void copy();
  void paste();
  void selectAll();

  void action_view_user_code();

  void action_clear_all_segments();
  void action_set_all_segments();

private:
  LCD* lcd;
  LCD_Registers* lcd_registers;

  Central_Widget* central_widget;

  QAction* menu_item_user_code;
  bool state_view_user_code = false;

  void create_file_menu();
  void create_edit_menu();
  void create_view_menu();
  void create_segment_menu();
};

#endif // MAIN_WINDOW_H
