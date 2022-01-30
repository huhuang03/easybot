//
// Created by huhua on 2021/10/10.
//

#ifndef PICTOOL_HSV_H
#define PICTOOL_HSV_H
#include <opencv2/opencv.hpp>
#include <iostream>

namespace eb {

/**
 * Use the half mode.
 * h 0 ~ 180
 * s 0 ~ 255
 * v 0 ~ 255
 */
class HSV {
 public:
  HSV();
  HSV(int h, int s, int v);
 public:
  static int H_MIN;
  static int H_MAX;
  static int S_MIN;
  static int S_MAX;
  static int V_MIN;
  static int V_MAX;

  // it's good for the public??
 private:
  int _h;
  int _s;
  int _v;

 public:
  int h() const;
  int s() const;
  int v() const;

  void setH(int h);
  void setS(int s);
  void setV(int v);

  cv::Scalar toScale() const;
  cv::Scalar toHMinScale() const;
  cv::Scalar toHMaxScale() const;
  cv::Vec3i toVec() const;

  friend std::ostream &operator<<(std::ostream &os, const HSV &thiz);

  bool operator==(const HSV &other) const;
  bool operator!=(const HSV &other) const;
};
}

#endif // constPICTOOL_HSV_H
