// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef LCD_H
#define LCD_H

#include <array>
#include <ostream>
#include <tuple>

#include <QObject>

class LCD: public QObject
{
  Q_OBJECT

public:
  LCD();

  static constexpr int DIGIT_MAX = 10;  // 10 digits, 0 to 9
  static constexpr int DIGIT_ANNUNCIATOR = -1;  // annuciators form a fake digit

  enum Segment_ID { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F,
		    SEG_G, SEG_DOT, SEG_COMMA, SEG_MAX };

  enum Annunciator_ID { ANN_NEGATIVE, ANN_USER, ANN_F_SHIFT, ANN_G_SHIFT,
			ANN_BEGIN, ANN_G, ANN_RAD, ANN_D_MY, ANN_C, ANN_PRGM, ANN_MAX };

  static const std::string& get_annunciator_name(int ann);

  class Segment
  {
  public:
    Segment();  // apparently we need a default constructor in order to use this class in a map
    Segment(int8_t digit, uint8_t segment);

    int8_t digit;
    uint8_t segment;

    friend bool operator<(const Segment& l, const Segment& r)
    {
      return std::tie(l.digit, l.segment) < std::tie(r.digit, r.segment);
    }
  };

  void clear();

  bool get_segment(Segment segment);
									 
public slots:
  void set_segment(Segment segment, bool new_state);

signals:
  void lcd_segment_state_changed(Segment segment, bool new_state);

private:
  std::array<std::array<bool, SEG_MAX>, DIGIT_MAX> digit_segment_state;
  std::array<bool, ANN_MAX> annunciator_state;
};

std::ostream& operator<<(std::ostream& os, const LCD::Segment& segment);

#endif // LCD_H

