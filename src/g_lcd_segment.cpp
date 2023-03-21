// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>

#include <QColor>

#include "g_lcd_segment.h"


static constexpr int outline_gray_level = 224;
static QColor segment_outline_color(outline_gray_level, outline_gray_level, outline_gray_level);
static QColor fill_color(0, 0, 0);


G_LCD_Segment::G_LCD_Segment(int segment,
			     QPainterPath& path,
			     QGraphicsItem* parent):
  QGraphicsPathItem(parent),
  segment(segment),
  state(false),
  pen { QPen(segment_outline_color), QPen(fill_color) },
  brush { QBrush(), QBrush(Qt::SolidPattern) }
{
  this->setPath(path);

  //pen.setColor(segment_outline_color);
  //this->setPen(pen);

  this->setPen(pen[state]);
  this->setBrush(brush[state]);

  if (false)
  {
    QRectF bound = boundingRect();
    std::cout << "segment " << segment << " bounding rect "
	      << bound.x() << " " << bound.y() << " "
	      << bound.width() << " " << bound.height() << "\n";
  }
}

void G_LCD_Segment::set_state(bool value)
{
  if (state == value)
    return;
  state = value;
  this->setPen(pen[state]);
  this->setBrush(brush[state]);
  emit segment_state_changed(segment, state);
}

bool G_LCD_Segment::get_state()
{
  return state;
}

void G_LCD_Segment::toggle_state()
{
  set_state(! state);
}

void G_LCD_Segment::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  toggle_state();
}
