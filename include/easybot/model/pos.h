//
// Created by hwf on 2022/1/5.
//

#ifndef EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
#define EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
#include <string>
#include <ostream>

namespace eb {

/**
 * 当前地图的坐标
 */
class Pos {
 private:
  int _x;
  int _y;
  /**
   * 地图名称
   * 但是有可能地图重名，遇到再增加一个name吧。
   */
  std::string _name;

 public:
  Pos(int x, int y, std::string name);
  int x() const;;
  int y() const;;
  std::string name();;
  friend std::ostream &operator<<(std::ostream &os, const Pos &pos);
};

}
#endif //EASYBOT_INCLUDE_EASYBOT_MODEL_POS_H_
