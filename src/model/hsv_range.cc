//
// Created by huhua on 2021/10/10.
//


#include <easybot/model/hsv_range.h>


eb::HSVRange::HSVRange(HSV h1, HSV h2) {
    this->_h1 = h1;
    this->_h2 = h2;
}

void eb::HSVRange::work(cv::InputArray in, cv::OutputArray out) {
    out.create(in.size(), in.type());
    // ok, let's do something.
    cv::Mat hsv;
    cv::cvtColor(in, hsv, cv::COLOR_RGB2HSV);

    cv::Mat mask;
    if (!this->isHCrossBoundary()) {
        cv::inRange(hsv, this->_h1.toScale(), this->_h2.toScale(), mask);
    } else {
        cv::Mat mask1;
        cv::inRange(hsv, this->_h1.toScale(), this->_h2.toHMaxScale(), mask);

        cv::Mat mask2;
        cv::inRange(hsv, this->_h1.toHMinScale(), this->_h2.toScale(), mask);

        cv::bitwise_or(mask1, mask2, mask);
    }

    cv::bitwise_and(in, in, out, mask);
}

bool eb::HSVRange::isHCrossBoundary() {
    return this->_h1.h() > this->_h2.h();
}
