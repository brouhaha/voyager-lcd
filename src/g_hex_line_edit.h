// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <string>

#include <QLineEdit>
#include <QWidget>

class G_Hex_Line_Edit: public QLineEdit
{
  Q_OBJECT

public:
  G_Hex_Line_Edit(int id,
		  unsigned digits = 14,
		  QWidget *parent = nullptr);

public slots:
  void set_value(uint64_t new_value);

signals:
  void value_changed(int id, uint64_t new_value);

private:
  int id;
  unsigned digits;
  uint64_t data;
  std::string s;
};
