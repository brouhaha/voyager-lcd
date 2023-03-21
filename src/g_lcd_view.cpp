// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QGraphicsScene>

#include "g_lcd_view.h"

G_LCD_View::G_LCD_View(LCD* lcd,
		       QWidget *parent):
  QGraphicsView(new QGraphicsScene, parent),
  lcd(lcd),
  g_lcd(new G_LCD())
{
  scene()->addItem(g_lcd);

  connect(g_lcd, &G_LCD::lcd_segment_state_changed,
	  lcd,   &LCD::set_segment);

  connect(lcd,   &LCD::lcd_segment_state_changed,
	  g_lcd, &G_LCD::lcd_segment_state_changed_in);
}

// https://stackoverflow.com/questions/10891962/how-to-fit-qgraphicsscene-in-a-qgraphicsview
void G_LCD_View::zoomToFit()
{
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void G_LCD_View::resizeEvent(QResizeEvent *event)
{
  zoomToFit();
}
