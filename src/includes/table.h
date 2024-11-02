//
// Created by 陈洋 on 24-11-2.
//

#ifndef TABLE_H
#define TABLE_H
#include <string>

class Symbol {
 public:
  Symbol() = default;
  Symbol(std::string name, std::string type)
      : name(std::move(name)), type(std::move(type)) {}
  std::string name;
  std::string type;
};

#endif  // TABLE_H
