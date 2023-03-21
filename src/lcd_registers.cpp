// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include "lcd_registers.h"

LCD_Registers::Bit::Bit():
  register_number(0),
  bit_number(0)
{
}

LCD_Registers::Bit::Bit(uint8_t register_number, uint8_t bit_number):
  register_number(register_number),
  bit_number(bit_number)
{
}

std::ostream& operator<<(std::ostream& os, const LCD_Registers::Bit& bit)
{
  return os << "Bit(" << ((int) bit.register_number) << ", " << ((int) bit.bit_number) << ")";
}

LCD_Registers::LCD_Registers()
{
  for (int register_number = REG_9; register_number < REG_MAX; register_number++)
    reg[register_number] = 0;
}

static const std::string register_name[LCD_Registers::REG_MAX] =
{
  [LCD_Registers::REG_9] = "reg 9",
  [LCD_Registers::REG_10] = "reg 10",
};

const std::string LCD_Registers::get_register_name(int register_number)
{
  return register_name[register_number];
}

uint64_t LCD_Registers::get_register(int register_number)
{
  return reg[register_number];
}

bool LCD_Registers::get_bit(int register_number, int bit_number)
{
  return (reg[register_number] >> bit_number) & 1;
}

void LCD_Registers::set_word(int register_number, uint64_t new_word)
{
  uint64_t old_word = reg[register_number];

  if (new_word == old_word)
    return;

  reg[register_number] = new_word;

  emit word_changed(register_number, old_word, new_word);
}

void LCD_Registers::set_bit(int register_number, int bit_number, bool new_bit)
{
  uint64_t old_word = reg[register_number];
  bool old_bit = (old_word >> bit_number) & 1;

  if (new_bit == old_bit)
    return;

  if (new_bit)
    reg[register_number] |= (1ULL << bit_number);
  else
    reg[register_number] &= ~(1ULL << bit_number);

  uint64_t new_word = reg[register_number];

  emit word_changed(register_number, old_word, new_word);
}
