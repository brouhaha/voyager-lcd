// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef LCD_REGISTERS_H
#define LCD_REGISTERS_H

#include <iostream>
#include <string>
#include <tuple>

#include <QObject>

#include "lcd.h"

class LCD_Registers: public QObject
{
  Q_OBJECT

public:
  static constexpr int BITS = 56;

  class Bit
  {
  public:
    Bit();  // apparently we need a default constructor in order to use this class in a map
    Bit(uint8_t register_number, uint8_t bit_number);

    uint8_t register_number;
    uint8_t bit_number;

    friend bool operator<(const Bit& l, const Bit& r)
    {
      return std::tie(l.register_number, l.bit_number) < std::tie(r.register_number, r.bit_number);
    }
  };

  LCD_Registers();

  enum Register_Number { REG_9, REG_10, REG_MAX };

  uint64_t get_register(int register_number);
  bool get_bit(int register_number, int bit_number);

  static const std::string get_register_name(int register_number);
									 
public slots:
  void set_word(int register_number, uint64_t new_word);
  void set_bit(int register_number, int bit_number, bool new_bit);

signals:
  void word_changed(int register_number, uint64_t old_word, uint64_t new_word);

private:
  uint64_t reg[REG_MAX];
};

std::ostream& operator<<(std::ostream& os, const LCD_Registers::Bit& bit);

#endif // LCD_REGISTERS_H
