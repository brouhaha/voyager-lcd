// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef HP15C_USER_CODE_H
#define HP15C_USER_CODE_H

#include <map>
#include <ostream>
#include <string>

class HP15C_User_Code
{
 protected:
  HP15C_User_Code();
  static HP15C_User_Code* instance;

 public:
  HP15C_User_Code(HP15C_User_Code&) = delete;                    // delete copy constructor
  HP15C_User_Code& operator=(const HP15C_User_Code&) = delete;   // delete copy assignment
  
  static HP15C_User_Code* get_instance();

  static std::string lookup(uint8_t single_byte);

  static std::string lookup(uint8_t first_byte, uint8_t second_byte);

  static void dump_table(std::ostream& out);

  static void dump_instructions(std::ostream &out);

 protected:
  static std::map<uint16_t, std::string> inst_mnemonic;

  static void build_table();
};

#endif // HP15C_USER_CODE_H
