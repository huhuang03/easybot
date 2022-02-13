//
// Created by huhua on 2022/2/13.
//

#include <easybot/util/util_comm.h>
#include <chrono>

long eb::currentTimeInMillisecond() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
      ).count();
}