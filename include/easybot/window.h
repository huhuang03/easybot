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
#define wid_t HWND
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
  cv::Rect2i _rect;

 public:
  explicit Window(wid_t _wid);
//  ~Window();
  std::string title;
  std::string className;
  cv::Rect2i rect(bool forceRefresh = false);
  std::vector<eb::Window> getSubWindows();

  static void printAllWindow();

  static bool findWindow(Window *out, const std::string &windowName);

  void moveCursor(int x, int y);

  /**
   * Find first window match the processName and windowName exactly
   * Caller close the resource.
   * @param processName the processName, pass "" will search for all process.
   * @param windowName the windowName
   * @return nullptr if not find.
   */
  static bool findWindow(Window *out, const std::string &processName, std::string windowName);

  wid_t getId() const;

  void refresh();

  static std::vector<Window> getTopVisibleWindows();

  std::string str() const;

  /**
   * @return get title dynamic
   */
  std::string getTitle();

  void screenshot(cv::OutputArray output, int scale = 1);

  friend std::ostream &operator<<(std::ostream &out, const Window &window);

  bool isVisible();

  bool isInScreen() const;

  /**
   * 是否是Ime之类的不可见窗口。暂时只在windows上判断
   */
  bool isImeStaff() const;

  // A window that has no parent, or whose parent is the desktop window, is called a top-level window.
  bool isTopLevel() const;

  /**
   * A normal window means
   */
  bool isNormalWindow();

  // https://devblogs.microsoft.com/oldnewthing/20200302-00/?p=103507
  bool isCloaked() const;

  bool isEnable() const;
};
}

#endif //EASYBOT_WINDOW_H