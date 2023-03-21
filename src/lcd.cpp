// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <stdexcept>
#include <iostream>

#include "lcd.h"


LCD::Segment::Segment():
  digit(0),
  segment(0)
{
}

LCD::Segment::Segment(int8_t digit, uint8_t segment):
  digit(digit),
  segment(segment)
{
}

std::ostream& operator<<(std::ostream& os, const LCD::Segment& segment)
{
  return os << "Segment(" << ((int) segment.digit) << ", " << ((int) segment.segment) << ")";
}

static constexpr std::string annunciator_name[LCD::ANN_MAX] =
{
  [LCD::ANN_NEGATIVE] = "NEGATIVE",
  [LCD::ANN_USER]     = "USER",
  [LCD::ANN_F_SHIFT]  = "f",
  [LCD::ANN_G_SHIFT]  = "g",
  [LCD::ANN_BEGIN]    = "BEGIN",
  [LCD::ANN_G]        = "G",
  [LCD::ANN_RAD]      = "RAD",
  [LCD::ANN_D_MY]     = "D.MY",
  [LCD::ANN_C]        = "C",
  [LCD::ANN_PRGM]     = "PRGM"
};



LCD::LCD()
{
  clear();
}

const std::string& LCD::get_annunciator_name(int ann)
{
  return annunciator_name[ann];
}

void LCD::clear()
{
  for (int digit = 0; digit < DIGIT_MAX; digit++)
    for (int segment = 0; segment < SEG_MAX; segment++)
      digit_segment_state.at(digit).at(segment) = false;
  for (int annunciator = 0; annunciator < ANN_MAX; annunciator++)
    annunciator_state.at(annunciator) = false;
}

bool LCD::get_segment(Segment segment)
{
  if (segment.digit == DIGIT_ANNUNCIATOR)
    return annunciator_state.at(segment.segment);
  else
    return digit_segment_state.at(segment.digit).at(segment.segment);
}

void LCD::set_segment(Segment segment, bool new_state)
{
  if (segment.digit == DIGIT_ANNUNCIATOR)
  {
    annunciator_state.at(segment.segment) = new_state;
    emit lcd_segment_state_changed(segment, new_state);
  }
  else
  {
    digit_segment_state.at(segment.digit).at(segment.segment) = new_state;
    emit lcd_segment_state_changed(segment, new_state);
  }
}
