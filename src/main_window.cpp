// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

#include "main_window.h"

Main_Window::Main_Window(LCD *lcd,
			 LCD_Registers *lcd_registers):
  central_widget(new Central_Widget(lcd, lcd_registers, this))
{
  setCentralWidget(central_widget);

  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

  QAction *aboutAction = fileMenu->addAction(tr("About voyager-lcd"));
  connect(aboutAction, &QAction::triggered, this, &Main_Window::about);
  fileMenu->addAction(aboutAction);

  fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
}

void Main_Window::closeEvent(QCloseEvent *event)
{
}

void Main_Window::about()
{
  QMessageBox::about(this,
		     tr("About voyager-lcd"),
		     tr("A program to compose data words for HP Voyager calculator LCD displays."));
}
