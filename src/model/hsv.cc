//
// Created by huhua on 2021/10/10.
//

#include <easybot/model/hsv.h>

int eb::HSV::H_MIN = 0;
int eb::HSV::H_MAX = 179;
int eb::HSV::S_MIN = 0;
int eb::HSV::S_MAX = 255;
int eb::HSV::V_MIN = 0;
int eb::HSV::V_MAX = 255;

int eb::HSV::h() const {
    return this->_h;
}

int eb::HSV::s() const {
    return this->_s;
}

int eb::HSV::v() const {
    return this->_v;
}

void eb::HSV::setH(int h) {
    this->_h = h;
}

void eb::HSV::setS(int s) {
    this->_s = s;
}

void eb::HSV::setV(int v) {
    this->_v = v;
}

cv::Scalar_<int> eb::HSV::toScale() {
    return cv::Scalar_<int>(this->h(), this->s(), this->v());
}

cv::Scalar_<int> eb::HSV::toHMinScale() {
    return cv::Scalar_<int>(H_MIN, this->s(), this->v());
}

cv::Scalar_<int> eb::HSV::toHMaxScale() {
    return cv::Scalar_<int>(H_MAX, this->s(), this->v());
}
