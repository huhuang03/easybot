//
// Created by hwf on 2022/1/5.
//

#ifndef EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
#define EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
#include <string>
#include <ostream>

namespace eb {

/**
 * 我想要可以表示简单位置和带地图名称位置的两种表示方法，怎么设计更好？
 */
class Pos {
 private:
  int _x;
  int _y;

 public:
  Pos(int x, int y);
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
