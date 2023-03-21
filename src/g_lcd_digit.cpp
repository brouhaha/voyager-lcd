// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <cmath>
#include <map>

#include <QList>
#include <QPainterPath>
#include <QPolygonF>
#include <QPointF>
#include <QTransform>

#include "g_lcd_digit.h"


static constexpr double segment_length = 29.00;
static constexpr double segment_width  =  7.00;
static constexpr double gap            =  1.00;

static constexpr double shear_angle_degrees = -10.0;



static constexpr double shear_angle_radians = shear_angle_degrees * M_PI / 180.0;


static QTransform transform_rotate_90_degrees = QTransform().rotate(90.0 /* degrees */);


static QPolygonF horizontal_segment_poly(QList<QPointF>({QPointF(-segment_length/2.0,                   0.0),
                                                         QPointF(-(segment_length-segment_width)/2.0,  -segment_width/2.0),
							 QPointF( (segment_length-segment_width)/2.0,  -segment_width/2.0),
							 QPointF( segment_length/2.0,                   0.0),
							 QPointF( (segment_length-segment_width)/2.0,   segment_width/2.0),
							 QPointF(-(segment_length-segment_width)/2.0,   segment_width/2.0),
							 QPointF(-segment_length/2.0,                   0.0)}));

static QPolygonF vertical_segment_poly = transform_rotate_90_degrees.map(horizontal_segment_poly);

static double dot_radius = 3.5;
static QPointF dot_center = QTransform().shear(shear_angle_radians, 0.0).map(QPointF(segment_length / 2.0 + segment_width + gap + dot_radius, segment_length + 2.0 * gap));

static double comma_radius = dot_radius + 1.5;
static double comma_angle_start_degrees = 210.0;
static double comma_angle_end_degrees = 265.0;
static QPointF comma_tip = dot_center + QPointF(-6.00, +9.0);


static QPainterPath polygon_path(QPolygonF polygon)
{
  QPainterPath path;
  path.addPolygon(polygon);
  return path;
}

static QPainterPath circle_path(const QPointF &center, double radius)
{
  QPainterPath path;
  path.addEllipse(center, radius, radius);
  return path;
}

static QPainterPath comma_tail_path(const QPointF &dot_center,
				    double radius,
				    double start_angle_degrees,
				    double end_angle_degrees,
				    QPointF &comma_tip)
{
  QPainterPath path;
  QRectF rect(dot_center.x()-radius,
	      dot_center.y()-radius,
	      2.0 * radius,
	      2.0 * radius);
  path.arcMoveTo(rect, start_angle_degrees);
  QPointF arc_start = path.currentPosition();
  path.arcTo(rect, start_angle_degrees, end_angle_degrees - start_angle_degrees);
  QPointF arc_end = path.currentPosition();
  path.lineTo(comma_tip);
  path.lineTo(arc_start);
  return path;
}

static QPainterPath segment_path[LCD::SEG_MAX] =
{
  [LCD::SEG_A]     = polygon_path(QTransform().shear(shear_angle_radians, 0.0).translate(                      0.0, -segment_length - gap * 2.0).map(horizontal_segment_poly)),
  [LCD::SEG_B]     = polygon_path(QTransform().shear(shear_angle_radians, 0.0).translate( segment_length/2.0 + gap, -segment_length/2.0 - gap)  .map(vertical_segment_poly)),
  [LCD::SEG_C]     = polygon_path(QTransform().shear(shear_angle_radians, 0.0).translate( segment_length/2.0 + gap,  segment_length/2.0 + gap)  .map(vertical_segment_poly)),
  [LCD::SEG_D]     = polygon_path(QTransform().shear(shear_angle_radians, 0.0).translate(                      0.0,  segment_length + gap * 2.0).map(horizontal_segment_poly)),
  [LCD::SEG_E]     = polygon_path(QTransform().shear(shear_angle_radians, 0.0).translate(-segment_length/2.0 - gap,  segment_length/2.0 + gap)  .map(vertical_segment_poly)),
  [LCD::SEG_F]     = polygon_path(QTransform().shear(shear_angle_radians, 0.0).translate(-segment_length/2.0 - gap, -segment_length/2.0 - gap)  .map(vertical_segment_poly)),
  [LCD::SEG_G]     = polygon_path(QTransform().shear(shear_angle_radians, 0.0).translate(                      0.0,  0.0)                       .map(horizontal_segment_poly)),
  [LCD::SEG_DOT]   = circle_path(dot_center, dot_radius),
  [LCD::SEG_COMMA] = comma_tail_path(dot_center,
				     comma_radius,
				     comma_angle_start_degrees,
				     comma_angle_end_degrees,
				     comma_tip)
};


G_LCD_Digit::G_LCD_Digit(int digit,
			 bool sign_only,
			 QGraphicsItem *parent,
			 Qt::WindowFlags wFlags):
  QGraphicsWidget(parent, wFlags),
  digit(digit),
  sign_only(sign_only)
{
  int first_segment = LCD::SEG_A;
  int last_segment = LCD::SEG_COMMA;

  if (sign_only)
  {
    first_segment = last_segment = LCD::SEG_G;
  }

  for (int s = first_segment; s <= last_segment; s++)
  {
    lcd_segment[s] = new G_LCD_Segment(s,
				       segment_path[s],
				       this);
    connect(lcd_segment[s], &G_LCD_Segment::segment_state_changed,
	    this,           &G_LCD_Digit::segment_state_changed_in);
  }
}

void G_LCD_Digit::set_segment(int segment, bool value)
{
  lcd_segment[segment]->set_state(value);
}

bool G_LCD_Digit::get_segment(int segment)
{
  return lcd_segment[segment]->get_state();
}

void G_LCD_Digit::segment_state_changed_in(int segment, bool new_state)
{
  emit digit_segment_state_changed(digit, segment, new_state);
}
