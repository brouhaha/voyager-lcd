// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>

#include <QByteArray>
#include <QFontDatabase>
#include <QGraphicsLinearLayout>

#include "Aileron-Bold.h"
#include "g_lcd.h"


static const std::string font_name = "Aileron-Bold";

static QByteArray Aileron_Bold_bytes((const char *) Aileron_Bold_otf, sizeof(Aileron_Bold_otf));


G_LCD::G_LCD(QGraphicsItem *parent,
	     Qt::WindowFlags wFlags):
  QGraphicsWidget(parent, wFlags),
  digits_layout(new QGraphicsLinearLayout(Qt::Horizontal)),
  annunciators_layout(new QGraphicsLinearLayout(Qt::Horizontal)),
  vbox_layout(new QGraphicsLinearLayout(Qt::Vertical))
{
  int font_id = QFontDatabase::addApplicationFontFromData(Aileron_Bold_bytes);

  setLayout(vbox_layout);

  // digits are numbered 0 to 9 from LSB (right) to MSB (left), plus a partial digit 10 for negative sign
  for (int i = LCD::DIGIT_MAX; i >= 0; i--)
  {
    digit[i] = new G_LCD_Digit(i,
			       i == LCD::DIGIT_MAX,  // sign_only
			       this);   // parent
    connect(digit[i], &G_LCD_Digit::digit_segment_state_changed,
	    this, &G_LCD::digit_segment_state_changed_in);
    digits_layout->addItem(digit[i]);
  }

  // skip ANN_NEGATIVE as it is turned into a leading digit
  for (int i = 0; i < LCD::ANN_MAX - 1; i++)
  {
    annunciator[i] = new G_LCD_Annunciator(i,
					   LCD::get_annunciator_name(i+1),
					   this);
    connect(annunciator[i], &G_LCD_Annunciator::annunciator_state_changed,
	    this, &G_LCD::annunciator_state_changed_in);
    annunciators_layout->addItem(annunciator[i]);

    if (false)
    {
      // this attempted at putting G and RAD close together failed
      Qt::Alignment alignment = Qt::AlignCenter;
      switch (i)
	{
	case LCD::ANN_G - 1:
	  alignment = Qt::AlignRight;
	  break;
	case LCD::ANN_RAD - 1:
	  alignment = Qt::AlignLeft;
	  break;
	}
      annunciators_layout->setAlignment(annunciator[i], alignment);
    }
  }

  if (false)
  {
    // this also isn't grat
    annunciators_layout->addStretch(LCD::ANN_MAX - 1);
  }

  vbox_layout->addItem(digits_layout);
  vbox_layout->addItem(annunciators_layout);
}

void G_LCD::set_segment(int digit, int segment, bool new_state)
{
  this->digit[digit]->set_segment(segment, new_state);
}

bool G_LCD::get_segment(int digit, int segment)
{
  return this->digit[digit]->get_segment(segment);
}

void G_LCD::digit_segment_state_changed_in(int digit, int segment, bool new_state)
{
  if (digit == LCD::DIGIT_MAX)
  {
    LCD::Segment s(LCD::DIGIT_ANNUNCIATOR, LCD::ANN_NEGATIVE);
    emit lcd_segment_state_changed(s, new_state);
  }
  else
  {
    LCD::Segment s(digit, segment);
    emit lcd_segment_state_changed(s, new_state);
  }
}

void G_LCD::annunciator_state_changed_in(int annunciator, bool new_state)
{
  // negative is handled as a digit
  LCD::Segment s(LCD::DIGIT_ANNUNCIATOR, annunciator+1);
  emit lcd_segment_state_changed(s, new_state);
}

void G_LCD::lcd_segment_state_changed_in(LCD::Segment segment, bool new_state)
{
  if (segment.digit == LCD::DIGIT_ANNUNCIATOR)
  {
    if (segment.segment == LCD::ANN_NEGATIVE)
      set_segment(LCD::DIGIT_MAX, LCD::SEG_G, new_state);
    else
      annunciator[segment.segment-1]->set_annunciator(new_state);
  }
  else
  {
    set_segment(segment.digit, segment.segment, new_state);
  }
}
