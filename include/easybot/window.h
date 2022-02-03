//
// Created by huhua on 2021/8/25.
//

#ifndef EASYBOT_WINDOW_H
#define EASYBOT_WINDOW_H

#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include <easybot/internal/global.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#elif defined(__APPLE__)
#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CGWindow.h>
#define wid_t CGWindowID
#endif

namespace eb {
// what do you think of this?
class Window {
 public:
  // why you have two titles?
 private:
  const static std::vector<std::string> VISIBLE_IGNORE_CLASS;
  wid_t wid;

 public:
  Window(wid_t _wid);
  std::string title;
  std::string className;
  cv::Rect2i rect;
  std::vector<eb::Window> getSubWindows();
  static bool findWindow(Window *out, const std::string &windowName);

  /**
   * Find first window match the processName and windowName exactly
   * Caller close the resource.
   * @param processName the processName, pass "" will search for all process.
   * @param windowName the windowName
   * @return nullptr if not find.
   */
  static bool findWindow(Window *out, const std::string &processName, std::string windowName);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  HWND hwnd;
  explicit Window(HWND hwnd);
#endif

  wid_t getId();

  void refresh();

  // A window that has no parent, or whose parent is the desktop window, is called a top-level window.
  bool isTopLevel() const;

  static std::vector<Window> getTopVisibleWindows();

  std::string str() const;

  bool isInScreen() const;

  // https://devblogs.microsoft.com/oldnewthing/20200302-00/?p=103507
  bool isCloaked() const;

  /**
   * @return get title dynamic
   */
  std::string getTitle();

  void screenshot(cv::OutputArray output);

  bool isVisible() const;

  friend std::ostream &operator<<(std::ostream &out, const Window &window);
};
}

#endif //EASYBOT_WINDOW_H