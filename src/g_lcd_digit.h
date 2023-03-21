// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_LCD_DIGIT_H
#define G_LCD_DIGIT_H

#include <string>

#include <QGraphicsItem>
#include <QGraphicsWidget>

#include "lcd.h"
#include "g_lcd_segment.h"

class G_LCD_Digit : public QGraphicsWidget
{
  Q_OBJECT

public:
  G_LCD_Digit(int digit,
	      bool signOnly = false,
	      QGraphicsItem *parent = nullptr,
	      Qt::WindowFlags wFlags = Qt::WindowFlags());

  bool get_segment(int segment);

public slots:
  void set_segment(int segment, bool value);

signals:
  void digit_segment_state_changed(int digit, int segment, bool new_state);

private slots:
  void segment_state_changed_in(int segment, bool new_state);

private:
  int digit;
  bool sign_only;

  G_LCD_Segment *lcd_segment[LCD::SEG_MAX];
};

#endif // G_LCD_DIGIT_H

