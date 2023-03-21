// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_LCD_ANNUNCIATOR_H
#define G_LCD_ANNUNCIATOR_H

#include <string>

#include <QGraphicsItem>
#include <QGraphicsWidget>

#include "lcd.h"
#include "g_lcd_segment.h"

class G_LCD_Annunciator : public QGraphicsWidget
{
  Q_OBJECT

public:
  G_LCD_Annunciator(int annunciator,
		    const std::string& text,
		    QGraphicsItem *parent = nullptr,
		    Qt::WindowFlags wFlags = Qt::WindowFlags());

  bool get_annunciator();

public slots:
  void set_annunciator(bool value);

signals:
  void annunciator_state_changed(int annunciator, bool new_state);

private slots:
  void segment_state_changed_in(int segment, bool new_state);

private:
  int annunciator;
  QPainterPath path;
  G_LCD_Segment *lcd_segment;
};

#endif // G_LCD_ANNUNCIATOR_H

