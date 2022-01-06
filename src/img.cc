//
// Created by hwf on 2022/1/6.
//

#include <easybot/img.h>
#include <opencv2/imgproc.hpp>
#include <utility>

cv::Mat eb::Img::hsv() {
  if (_hsvImg.empty()) {
    cv::cvtColor(this->_img, this->_hsvImg, cv::COLOR_BGR2HSV);
  }
  return _hsvImg;
}

eb::Img::Img(cv::Mat img): _img(std::move(img)) {}

cv::Mat eb::Img::applyHsv(const eb::HSVRange &range) {
  return cv::Mat();
}
