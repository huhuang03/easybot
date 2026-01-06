//
// Created by huhua on 2021/10/10.
//

#ifndef EASYBOT_HSV_RANGE_H
#define EASYBOT_HSV_RANGE_H
#include "./hsv.h"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace eb {
class HSVRange {
  HSV _h1;
  HSV _h2;

  // named lower and upper is better?
 public:
  HSVRange();
  HSVRange(HSV h1, HSV v2);

  [[nodiscard]] HSV h1() const;
  [[nodiscard]] HSV h2() const;

  /**
   * h是否跨了边界
   * @return
   */
  bool isHCrossBoundary() const;

  void work(cv::InputArray in, cv::OutputArray out) const;

  friend std::ostream &operator<<(std::ostream &os, const HSVRange &thiz);

  bool operator==(const HSVRange &other) const;
  bool operator!=(const HSVRange &other) const;

};
}
#endif //EASYBOT_HSV_RANGE_H
