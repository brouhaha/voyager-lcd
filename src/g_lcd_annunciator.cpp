// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QFont>
#include <QPainterPath>

#include "g_lcd_annunciator.h"


static const QString font_name("Aileron");
static const int font_point_size = 12;
static const int font_weight = QFont::Bold;
static const bool font_italic = false;


static QFont* xfont = nullptr;


G_LCD_Annunciator::G_LCD_Annunciator(int annunciator,
				     const std::string& text,
				     QGraphicsItem *parent,
				     Qt::WindowFlags wFlags):
  QGraphicsWidget(parent, wFlags),
  annunciator(annunciator)
{
  if (xfont == nullptr)
  {
    xfont = new QFont(font_name, font_point_size, font_weight, font_italic);
  }

  double x = 0.0;
  double y = 0.0;
  
  path.addText(x, y, *xfont, QString::fromStdString(text));

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
