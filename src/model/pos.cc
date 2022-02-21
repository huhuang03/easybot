//
// Created by hwf on 2022/1/5.
//
#include <easybot/model/pos.h>

eb::Pos::Pos(int x, int y): _x(x), _y(y) {
}

int eb::Pos::x() const {return _x;}

int eb::Pos::y() const {return _y;}

std::ostream &eb::operator<<(std::ostream &os, const eb::Pos &pos) {
  os << "_x: " << pos._x << " _y: " << pos._y << " _name: ";
  return os;
}

bool eb::Pos::operator==(const eb::Pos &other) const {
  return other.x() == this->x() && other.y() == this->y();
}

//bool eb::operator==(const eb::Pos &thiz, const eb::Pos &other) {
//  return other.name() == thiz.name() && other.x() == thiz.x() && other.y() == thiz.y();
//}

double eb::Pos::distance(const eb::Pos &other) {
  return sqrt(pow(other.x() - this->x(), 2) + pow(other.y() - this->y(), 2));
}

bool eb::Pos::isNear(const eb::Pos &other, int distance) {
  return isNear(other, (double)distance);
}

bool eb::Pos::isNear(const eb::Pos &other, double distance) {
  return this->distance(other) < distance;
}

