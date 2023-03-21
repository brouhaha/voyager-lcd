// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_LCD_VIEW_H
#define G_LCD_VIEW_H

#include <QGraphicsView>
#include <QResizeEvent>

#include "lcd.h"
#include "g_lcd.h"

class G_LCD_View : public QGraphicsView
{
public:
  G_LCD_View(LCD* lcd,
	     QWidget *parent = nullptr);

  void zoomToFit();

protected:
  void resizeEvent(QResizeEvent *event) override;

private:
  LCD* lcd;
  G_LCD* g_lcd;
};

#endif // G_LCD_VIEW_H