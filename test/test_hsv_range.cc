//
// Created by huhua on 2021/10/16.
//

#include <gtest/gtest.h>
#include <easybot/model/hsv_range.h>
#include <easybot/model/coordinate.h>

TEST(HsvRangeTest, testCout) {
  auto hsvRange = eb::HSVRange(eb::HSV(), eb::HSV());
  std::cout << hsvRange << std::endl;
  std::cout << hsvRange.h1().toScale() << std::endl;
  eb::Coordinate coord;
}