// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_LCD_SEGMENT_H
#define G_LCD_SEGMENT_H

#include <map>

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>

class G_LCD_Segment : public QObject, public QGraphicsPathItem
{
  Q_OBJECT

public:
  G_LCD_Segment(int segment,
		QPainterPath& path,
		QGraphicsItem* parent = nullptr);

  bool get_state();

public slots:
  void set_state(bool value);
  void toggle_state();

signals:
  void segment_state_changed(int segment, bool newState);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  int segment;
  bool state;
  QPen pen[2];
  QBrush brush[2];
};

#endif // G_LCD_SEGMENT_H

