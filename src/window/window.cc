//
// Created by huhua on 2021/8/25.
//

#include "easybot/window.h"
#include "easybot/util/util_cv.h"

#if __APPLE__
#include <ApplicationServices/ApplicationServices.h>
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <dwmapi.h>
#include <WinUser.h>
#endif

static std::string TITLE_MSCTFIME_UI = "MSCTFIME UI";
static std::string TITLE_DEFAULT_IME = "Default IME";

// yes, I think this go in program
// Program is the class name of Program Manager
const std::vector<std::string> eb::Window::VISIBLE_IGNORE_CLASS{"Progman"};

struct EnumChildWindowsGetSubWindowsParam {
  std::vector<eb::Window> *rst;
};

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
BOOL enumChildWindowsGetSubWindows(HWND hwnd, LPARAM param) {
  auto *config = reinterpret_cast<EnumChildWindowsGetSubWindowsParam *>(param);
  config->rst->push_back(eb::Window(hwnd));
  return TRUE;
}

eb::Window::Window(HWND hwnd) : hwnd(hwnd) {
  this->refresh();
}

static BOOL WINAPI enumWindowGetTopVisibleWindows(HWND hwnd, LPARAM param) {
  auto *windows = (std::vector<eb::Window> *) param;
  // should I check?
  // I still can't find the top level window.
  // A window that has no parent, or whose parent is the desktop window, is called a top-level window.
  auto window = eb::Window(hwnd);

  // For now we don't check screen region because it seems need check many screen.
  if (window.isTopLevel() && window.isInScreen()) {
    windows->push_back(window);
  }
  return true;
}


static struct ParamEnumFindWindow {
  DWORD processId;
  std::string *windowName;
  HWND *hwnd = nullptr;
};

static BOOL CALLBACK enumFindWindow(HWND hwnd, LPARAM param) {
  // hwo to do?
  char title[1024];
  auto *config = (ParamEnumFindWindow *) param;
  GetWindowText(hwnd, (LPSTR) &title, 1023);
  DWORD processId;
  GetWindowThreadProcessId(hwnd, &processId);

  if (config->processId == processId
      && ((title == *config->windowName) || (eb::gbk2utf8(title) == *config->windowName))) {
    // how to let the window open?
    *config->hwnd = hwnd;
    return FALSE;
  }
  return TRUE;
}

HWND eb::findWindow(const std::string &processName, std::string windowName) {
  auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (!thSnap) {
    return nullptr;
  }
  PROCESSENTRY32 pe;

  // need close pe?
  if (!Process32Next(thSnap, &pe)) {
    return nullptr;
  }

  const bool ignoreName = processName.empty();

  HWND rst = nullptr;
  do {
    if (ignoreName || processName == pe.szExeFile) {
      // ok, we find the process
      // but how can we get the window?
      struct ParamEnumFindWindow param{
          pe.th32ProcessID,
          &windowName,
          &rst
      };
      EnumWindows(enumFindWindow, reinterpret_cast<LPARAM>(&param));
    }
  } while (Process32Next(thSnap, &pe));

  CloseHandle(thSnap);
  return rst;
}

HWND eb::findWindow(const std::string &windowName) {
  return eb::findWindow("", windowName);
}

static void getMat(HWND hWND, cv::OutputArray out) {
  HDC deviceContext = GetDC(hWND);
  HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);

  RECT windowRect;
  GetClientRect(hWND, &windowRect);

  int height = windowRect.bottom;
  int width = windowRect.right;

  HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, width, height);

  SelectObject(memoryDeviceContext, bitmap);

  //copy data into bitmap
  BitBlt(memoryDeviceContext, 0, 0, width, height, deviceContext, 0, 0, SRCCOPY);


  //specify format by using bitmapinfoheader!
  BITMAPINFOHEADER bi;
  bi.biSize = sizeof(BITMAPINFOHEADER);
  bi.biWidth = width;
  bi.biHeight = -height;
  bi.biPlanes = 1;
  bi.biBitCount = 32;
  bi.biCompression = BI_RGB;
  bi.biSizeImage = 0; //because no compression
  bi.biXPelsPerMeter = 1; //we
  bi.biYPelsPerMeter = 2; //we
  bi.biClrUsed = 3; //we ^^
  bi.biClrImportant = 4; //still we

  out.create(height, width, CV_8UC4);

  cv::Mat img;
  GetDIBits(memoryDeviceContext, bitmap, 0, height, out.getMatRef().data, (BITMAPINFO *) &bi, DIB_RGB_COLORS);

  //clean up!
  DeleteObject(bitmap);
  DeleteDC(memoryDeviceContext); //delete not release!
  ReleaseDC(hWND, deviceContext);
}

void eb::screenshot(HWND hwnd, cv::OutputArray out) {
  getMat(hwnd, out);
}
#endif

std::vector<eb::Window> eb::Window::getSubWindows() {
  std::vector<eb::Window> rst;
  struct EnumChildWindowsGetSubWindowsParam param{
      &rst,
  };

  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  EnumChildWindows(this->hwnd, enumChildWindowsGetSubWindows, reinterpret_cast<LPARAM>(&param));
  #endif
  return rst;
}


void eb::Window::refresh() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  if (this->hwnd == nullptr) {
    return;
  }
  this->title = this->getTitle();

  RECT r;
  GetWindowRect(this->hwnd, &r);
  this->rect = rectWin2cv(r);

  TCHAR cName[MAX_PATH + 1];
  GetClassName(hwnd, cName, _countof(cName));
  this->className = std::string(cName);
#endif
}


std::vector<eb::Window> eb::Window::getTopVisibleWindows() {
  auto rst = std::vector<Window>();
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  EnumWindows(enumWindowGetTopVisibleWindows, (LPARAM) &rst);
#endif
  return rst;
}

bool eb::Window::isTopLevel() const {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  return this->hwnd == GetAncestor(this->hwnd, GA_ROOT);
#endif
  return false;
}

std::string eb::Window::str() const {
  return "Window(title: " + this->title + ", rect: " + eb::to_string(this->rect) + ")";
}

bool eb::Window::isCloaked() const {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  BOOL isCloaked = FALSE;
  return SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED,
                                         &isCloaked, sizeof(isCloaked))) && isCloaked;
  #endif
  return false;
}

bool eb::Window::isInScreen() const {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  if (this->isCloaked()) {
    return false;
  }
  if (std::count(Window::VISIBLE_IGNORE_CLASS.begin(), Window::VISIBLE_IGNORE_CLASS.end(), this->className)) {
    return false;
  }
  if (this->rect.width == 0 || this->rect.height == 0) {
    return false;
  }
  return !IsIconic(hwnd) && IsWindowVisible(hwnd);
#endif
  return false;
}

std::string eb::Window::getTitle() {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  auto len = GetWindowTextLength(hwnd);
  auto pszMem = (PSTR) VirtualAlloc((LPVOID) NULL,
                                    (DWORD) (len + 1), MEM_COMMIT,
                                    PAGE_READWRITE);
  GetWindowText(hwnd, pszMem,
                len + 1);
  auto rst = std::string(pszMem);
  VirtualFree(pszMem, (DWORD) (len + 1), MEM_DECOMMIT);
  return rst;
  #endif
  return "";
}

void eb::Window::screenshot(const cv::_OutputArray &output) {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  eb::screenshot(this->hwnd, output);
  #endif

  std::cout << "wid: " << wid << std::endl;
  // how to do this?
  auto imgRef = CGWindowListCreateImage(CGRectInfinite,
                                        kCGWindowListOptionIncludingWindow | kCGWindowListExcludeDesktopElements,
//                                        kCGWindowListOptionOnScreenOnly,
                                        this->wid, kCGWindowImageDefault);
  CGColorSpaceRef colorSpace = CGImageGetColorSpace(imgRef);

  // width: 2880
  // height: 1800
  // 系统也是这么大
  auto width = CGImageGetWidth(imgRef);
  auto height = CGImageGetHeight(imgRef);
  std::cout << "width: " << width << "height: " << height << std::endl;
  cv::Mat cvMat(height, width, CV_8UC4); // 8 bits per component, 4 channels

  CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,                 // Pointer to backing data
                                                  width,                      // Width of bitmap
                                                  height,                     // Height of bitmap
                                                  8,                          // Bits per component
                                                  cvMat.step[0],              // Bytes per row
                                                  colorSpace,                 // Colorspace
                                                  kCGImageAlphaNoneSkipLast |
                                                      kCGBitmapByteOrderDefault); // Bitmap info flags

  CGContextDrawImage(contextRef, CGRectMake(0, 0, width, height), imgRef);
  CGContextRelease(contextRef);
  CGImageRelease(imgRef);
  cv::imshow("img", cvMat);
  cv::waitKey(0);
//  std::cout << "imgRef: " << imgRef << std::endl;
}

std::ostream &eb::operator<<(std::ostream &out, const eb::Window &window) {
  out << window.str();
  return out;
}

bool eb::Window::isVisible() const {
  return false;
}

eb::Window::Window(wid_t _wid): wid(_wid) {
}

wid_t eb::Window::getId() {
  return this->wid;
}
