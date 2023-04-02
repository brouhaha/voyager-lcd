// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

// using the <cstdio> for snprintf - would much prefer to use
// <format> for std::format
#include <cstdio>

#include "g_user_code.h"
#include "hp15c_user_code.h"

G_User_Code::G_User_Code(int id,
			 QWidget *parent):
  QTextEdit(parent),
  id(id),
  data(0)
{
  setReadOnly(true);
  decode();
}

void G_User_Code::set_value(uint64_t new_value)
{
  if (new_value == data)
    return;

  data = new_value;

  decode();
}

void G_User_Code::decode()
{
  uint8_t bytes[7];

  decoded.clear();

  for (int i = 0; i < 7; i++)
    bytes[i] = (data >> (i * 8)) & 0xff;

  int i = 0;
  while (i < 7)
  {
    bool two_bytes = HP15C_User_Code::is_prefix(bytes[i]);
    char hex[7];
    //std::string hex;
    std::string mnemonic;
    if (two_bytes && (i != 6))
    {
      snprintf(hex, sizeof(hex), "%02x %02x ", bytes[i], bytes[i+1]);
      //hex = std::format("%02x %02x ", bytes[i], bytes[i+1]);
      mnemonic = HP15C_User_Code::lookup(bytes[i], bytes[i+1]);
    }
    else
    {
      snprintf(hex, sizeof(hex), "%02x    ", bytes[i]);
      //hex = std::format("%02x    ", bytes[i]);
      mnemonic = HP15C_User_Code::lookup(bytes[i]);
    }
    if (mnemonic.empty())
    {
      mnemonic = "-- invalid --";
    }
    decoded.append(hex);
    decoded.append(mnemonic);
    decoded.append("\n");
    i += two_bytes ? 2 : 1;
  }

  setText(QString::fromStdString(decoded));
}
