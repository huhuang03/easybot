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

eb::HSV::HSV(): HSV(0, 0, 0) {}

eb::HSV::HSV(int h, int s, int v): _h(h), _s(s), _v(v) { }

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

cv::Scalar_<int> eb::HSV::toScale() const {
    return cv::Scalar_<int>(this->h(), this->s(), this->v());
}

cv::Scalar_<int> eb::HSV::toHMinScale() const {
    return cv::Scalar_<int>(H_MIN, this->s(), this->v());
}

cv::Scalar_<int> eb::HSV::toHMaxScale() const {
    return cv::Scalar_<int>(H_MAX, this->s(), this->v());
}

std::ostream& eb::operator<<(std::ostream &os, const eb::HSV &thiz) {
    os << "(" << thiz.h() << ", " << thiz.s() << ", " << thiz.v() << ")";
    return os;
}
