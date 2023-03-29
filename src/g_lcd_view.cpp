// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QGraphicsScene>
#include <QSizePolicy>

#include "g_lcd_view.h"

G_LCD_View::G_LCD_View(LCD* lcd,
		       QWidget *parent):
  QGraphicsView(new QGraphicsScene, parent),
  lcd(lcd),
  g_lcd(new G_LCD())
{
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  scene()->addItem(g_lcd);

  connect(g_lcd, &G_LCD::lcd_segment_state_changed,
	  lcd,   &LCD::set_segment);

  connect(lcd,   &LCD::lcd_segment_state_changed,
	  g_lcd, &G_LCD::lcd_segment_state_changed_in);
}

QSize G_LCD_View::sizeHint() const
{
  return QSize(800, 200);
}

// https://stackoverflow.com/questions/10891962/how-to-fit-qgraphicsscene-in-a-qgraphicsview
void G_LCD_View::zoomToFit()
{
  fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void G_LCD_View::resizeEvent(QResizeEvent *event)
{
  zoomToFit();
  QGraphicsView::resizeEvent(event);
}

void G_LCD_View::paintEvent(QPaintEvent *event)
{
  // On Linux, just overriding resizeEvent to call zoomToFit is sufficient
  // that the view is sized appropriately at startup. On Windows, that
  // doesn't work, and explicitly calling zoomToFit in the constructor,
  // or various other places, doesn't work. Doing it on the first paint
  // event does the job.
  static bool first_time = true;
  if (first_time)
  {
    first_time = false;
    zoomToFit();
  }
  QGraphicsView::paintEvent(event);
}

