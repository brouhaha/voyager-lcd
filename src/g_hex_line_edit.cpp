// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QString>

#include "g_hex_line_edit.h"

G_Hex_Line_Edit::G_Hex_Line_Edit(int id,
				 unsigned digits,
				 QWidget *parent):
  QLineEdit(parent),
  id(id),
  digits(digits),
  data(0),
  s(digits, '0')
{
  setReadOnly(true);
  setText(QString::fromStdString(s));
}

void G_Hex_Line_Edit::set_value(uint64_t new_value)
{
  if (new_value == data)
    return;

  data = new_value;
  for (int i = 0; i < digits; i++)
  {
    if ((new_value & 0xf) <= 9)
      s[digits - 1 - i] = '0' + (new_value & 0xf);
    else
      s[digits - 1 - i] = 'a' + ((new_value & 0xf) - 10);
    new_value >>= 4;
  }
  setText(QString::fromStdString(s));
  emit value_changed(id, data);
}
