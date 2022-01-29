//
// Created by huhua on 2021/10/10.
//


#include <easybot/model/hsv_range.h>

eb::HSVRange::HSVRange(HSV h1, HSV h2) {
  this->_h1 = h1;
  this->_h2 = h2;
}

// why this effect in?
void eb::HSVRange::work(cv::InputArray in, cv::OutputArray out) {
  out.create(in.size(), in.type());
  // ok, let's do something.
  cv::Mat hsv;
  cv::cvtColor(in, hsv, cv::COLOR_RGB2HSV);

  cv::Mat mask;
  if (!this->isHCrossBoundary()) {
    std::cout << "_h1: " << this->_h1 << ", _h2: " << this->_h2  << std::endl;
    cv::inRange(hsv, this->_h1.toScale(), this->_h2.toScale(), mask);
  } else {
    cv::Mat mask1;
    cv::inRange(hsv, this->_h1.toScale(), this->_h2.toHMaxScale(), mask1);

    cv::Mat mask2;
    cv::inRange(hsv, this->_h1.toHMinScale(), this->_h2.toScale(), mask2);

    cv::bitwise_or(mask1, mask2, mask);
  }
  cv::bitwise_and(in, in, out, mask);
}

bool eb::HSVRange::isHCrossBoundary() {
  return this->_h1.h() > this->_h2.h();
}

std::ostream &eb::operator<<(std::ostream &os, const eb::HSVRange &thiz) {
  os << "[" << thiz._h1 << " - " << thiz._h2 << "]";
  return os;
}

eb::HSV eb::HSVRange::h2() const {
  return this->_h2;
}

eb::HSV eb::HSVRange::h1() const {
  return this->_h1;
}
