// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_LCD_H
#define G_LCD_H

#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>

#include "lcd.h"
#include "g_lcd_digit.h"
#include "g_lcd_annunciator.h"

class G_LCD : public QGraphicsWidget
{
  Q_OBJECT

public:
  G_LCD(QGraphicsItem* parent = nullptr,
	Qt::WindowFlags wFlags = Qt::WindowFlags());

  bool get_segment(int digit, int segment);
									 
public slots:
  void set_segment(int digit, int segment, bool new_state);

  // from LCD:
  void lcd_segment_state_changed_in(LCD::Segment segment, bool new_state);

signals:
  void lcd_segment_state_changed(LCD::Segment segment, bool new_state);

private slots:
  // from G_LCD_Digit:
  void digit_segment_state_changed_in(int digit, int segment, bool new_state);

  // from G_LCD_Segment:
  void annunciator_state_changed_in(int annunciator, bool new_state);

private:
  G_LCD_Digit* digit[LCD::DIGIT_MAX + 1];  // add one for negative, which is an extra partial digit
  G_LCD_Annunciator* annunciator[LCD::ANN_MAX - 1];  // less one for negative]

  QGraphicsLinearLayout* digits_layout;
  QGraphicsLinearLayout* annunciators_layout;
  QGraphicsLinearLayout* vbox_layout;
};

#endif // G_LCD_H

