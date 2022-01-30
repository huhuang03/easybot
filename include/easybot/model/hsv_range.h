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
 private:
  // use pointer look like good, but I don't want
  // to do like this.
  HSV _h1;
  HSV _h2;

  // named lower and upper is better?
 public:
  HSVRange(HSV h1, HSV v2);

  HSV h1() const;
  HSV h2() const;

  /**
   * h是否跨了边界
   * @return
   */
  bool isHCrossBoundary();

  void work(cv::InputArray in, cv::OutputArray out);

  friend std::ostream &operator<<(std::ostream &os, const HSVRange &thiz);

  bool operator==(const HSVRange &other) const;
  bool operator!=(const HSVRange &other) const;

};
}
#endif //EASYBOT_HSV_RANGE_H
