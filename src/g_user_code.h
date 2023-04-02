// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef G_USER_CODE_H
#define G_USER_CODE_H

#include <string>

#include <QTextEdit>

class G_User_Code: public QTextEdit
{
  Q_OBJECT

public:
  G_User_Code(int id,
	      QWidget *parent = nullptr);

public slots:
  void set_value(uint64_t new_value);

private:
  int id;
  uint64_t data;
  std::string decoded;

  void decode();
};

#endif // G_USER_CODE_H
