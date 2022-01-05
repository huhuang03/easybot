//
// Created by hwf on 2022/1/5.
//
#include <easybot/model/pos.h>

eb::Pos::Pos(int x, int y, std::string name): _x(x), _y(y), _name(std::move(name)) {}

int eb::Pos::x() const {return _x;}

int eb::Pos::y() const {return _y;}

std::string eb::Pos::name() {return _name;}

std::ostream &eb::operator<<(std::ostream &os, const eb::Pos &pos) {
  os << "_x: " << pos._x << " _y: " << pos._y << " _name: " << pos._name;
  return os;
}