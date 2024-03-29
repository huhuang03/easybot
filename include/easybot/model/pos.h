//
// Created by hwf on 2022/1/5.
//

#ifndef EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
#define EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
#include <string>
#include <ostream>

namespace eb {

class Pos {
 private:
  int _x;
  int _y;

 public:
  static int NO_POS;
  Pos(int x, int y);
  Pos();
  int x() const;;
  int y() const;;
  bool isNear(const Pos &other, double distance);
  bool isNear(const Pos &other, int distance);
  double distance(const Pos &other);

  bool operator==(const Pos &other) const;
//  friend bool operator==(const Pos &thiz, const Pos &other);
  friend std::ostream &operator<<(std::ostream &os, const Pos &pos);
};

}
#endif //EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
