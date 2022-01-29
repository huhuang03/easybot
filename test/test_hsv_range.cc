//
// Created by huhua on 2021/10/16.
//

#include <gtest/gtest.h>
#include <easybot/model/hsv_range.h>

TEST(HsvRangeTest, testCout) {
  auto hsvRange = eb::HSVRange(eb::HSV(), eb::HSV());
  std::cout << hsvRange << std::endl;
  std::cout << hsvRange.h1().toScale() << std::endl;
}

TEST(HsvRangeTest, testEqual) {
  eb::HSVRange hr1{{10, 20, 30}, {50, 39, 90}};
  eb::HSVRange hr2{{10, 20, 30}, {50, 39, 90}};
  ASSERT_TRUE(hr1 == hr2);
}
