// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QPainterPath>

#include "g_lcd_annunciator.h"

G_LCD_Annunciator::G_LCD_Annunciator(int annunciator,
				     const std::string& text,
				     QGraphicsItem *parent,
				     Qt::WindowFlags wFlags):
  QGraphicsWidget(parent, wFlags),
  annunciator(annunciator)
{
  double x = 0.0;
  double y = 0.0;
  
  path.addText(x, y, QFont(), QString::fromStdString(text));

  lcd_segment = new G_LCD_Segment(annunciator,
				  path,
				  this);
  connect(lcd_segment, &G_LCD_Segment::segment_state_changed,
	  this, &G_LCD_Annunciator::segment_state_changed_in);
}

void G_LCD_Annunciator::set_annunciator(bool value)
{
  lcd_segment->set_state(value);
}

bool G_LCD_Annunciator::get_annunciator()
{
  return lcd_segment->get_state();
}

void G_LCD_Annunciator::segment_state_changed_in(int segment, bool new_state)
{
  emit annunciator_state_changed(annunciator, new_state);
}
