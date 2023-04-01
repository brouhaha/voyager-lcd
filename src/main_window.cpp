// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

#include "main_window.h"

Main_Window::Main_Window(LCD *lcd,
			 LCD_Registers *lcd_registers):
  central_widget(new Central_Widget(lcd, lcd_registers, this))
{
  setCentralWidget(central_widget);

  create_file_menu();
  create_edit_menu();
}

    

void Main_Window::create_file_menu()
{
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

  QAction *aboutAction = fileMenu->addAction(tr("About voyager-lcd"));
  connect(aboutAction, &QAction::triggered, this, &Main_Window::about);

  (void) fileMenu->addSeparator();

  QAction *quitAction = fileMenu->addAction(tr("&Quit"));
  quitAction->setShortcuts(QKeySequence::Quit);
  connect(quitAction, &QAction::triggered, this, &Main_Window::close);
}


void Main_Window::create_edit_menu()
{
  QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

#if 0
  QAction *cutAction = editMenu->addAction(tr("Cu&t"));
  cutAction->setShortcuts(QKeySequence::Cut);
  cutAction->setStatusTip(tr("Cut the selection to the clipboard"));
  connect(cutAction, &QAction::triggered, this, &Main_Window::cut);

  QAction *copyAction = editMenu->addAction(tr("&Copy"));
  copyAction->setShortcuts(QKeySequence::Copy);
  copyAction->setStatusTip(tr("Copy the selection to the clipboard"));
  connect(copyAction, &QAction::triggered, this, &Main_Window::copy);

  QAction *pasteAction = editMenu->addAction(tr("&Paste"));
  pasteAction->setShortcuts(QKeySequence::Paste);
  pasteAction->setStatusTip(tr("Paste the clipboard into the selection"));
  connect(pasteAction, &QAction::triggered, this, &Main_Window::paste);

  (void) editMenu->addSeparator();

  QAction *selectAllAction = editMenu->addAction(tr("Select &All"));
  selectAllAction->setShortcuts(QKeySequence::SelectAll);
  selectAllAction->setStatusTip(tr("Select all"));
  connect(selectAllAction, &QAction::triggered, this, &Main_Window::selectAll);
#endif
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

void Main_Window::cut()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget *widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit *>(widget);
  if (line_edit)
  {
    // The following should normally be emitted as a signal, not a direct
    // method call. However, we have to emit the signal to only the focused
    // object, so we can't keep connections open permanently. Rather than
    // constantly connecting and disconnecting, we could use
    // QMetaObject::invokeMethod() with Qt::QueuedConnection or
    // Qt::QAutoConnection.
    // However, since this is for activation of a menu item or keyboard
    // shortcut, we should already be in the GUI thread, so callint the
    // widget directly should be OK.
    // See:
    //   https://stackoverflow.com/questions/3297456/invoke-slot-method-without-connection
    // and the QMetaObject docuemntation.
    line_edit->cut();
    return;
  }
}

void Main_Window::copy()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget *widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit *>(widget);
  if (line_edit)
  {
    // See comments in the cut method above.
    line_edit->copy();
    return;
  }
}

void Main_Window::paste()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget *widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit *>(widget);
  if (line_edit)
  {
    // See comments in the cut method above.
    line_edit->paste();
    return;
  }
}

void Main_Window::selectAll()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget *widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit *>(widget);
  if (line_edit)
  {
    // See comments in the cut method above.
    line_edit->selectAll();
    return;
  }
}
