//
// Created by hwf on 2022/1/6.
//

#ifndef EASYBOT_INCLUDE_EASYBOT_IMG_H_
#define EASYBOT_INCLUDE_EASYBOT_IMG_H_
/**
 * I didn't determine that should I create a class like this.
 * Maybe the raw cv::Mat is better? For now, I just write and see the
 * situation after.
 *
 * Ok, let's stop now. maybe later.
 */
#include <opencv2/core.hpp>
#include <easybot/model/hsv_range.h>

namespace eb {
class Img {
 private:
  cv::Mat _img;
  cv::Mat _hsvImg;

 public:
  explicit Img(cv::Mat img);

  /**
   * But the opencv api style is something else. how do you think
   * apply that type?
   * @return the hsv image
   */
  cv::Mat hsv();

  /**
   * Apply the hsv filter.
   * internal: for now, we don't cache
   */
  cv::Mat applyHsv(const HSVRange &range);
};
}
#endif //EASYBOT_INCLUDE_EASYBOT_IMG_H_
