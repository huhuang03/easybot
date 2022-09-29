//
// Created by huhua on 2021/8/25.
//

#include <easybot/window.h>
#include <easybot/util/util_cv.h>
#include <easybot/util/util_string.h>

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
BOOL CALLBACK enumChildWindowsGetSubWindows(HWND hwnd, LPARAM param) {
  auto *config = reinterpret_cast<EnumChildWindowsGetSubWindowsParam *>(param);
  config->rst->push_back(eb::Window(hwnd));
  return TRUE;
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


struct ParamEnumFindWindow {
  DWORD processId{};
  std::string *windowName{};
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

/**
 * @param scale 有些高分辨率上乘了scale倍
 */
static void getMat(HWND hWND, cv::OutputArray out, int scale = 1) {
  HDC deviceContext = GetDC(hWND);
  HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);

  RECT windowRect;
  GetClientRect(hWND, &windowRect);

  int height = windowRect.bottom / scale;
  int width = windowRect.right / scale;

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
  bi.biBitCount = 3 * 8;
  bi.biCompression = BI_RGB;
  bi.biSizeImage = 0; //because no compression
  bi.biXPelsPerMeter = 1; //we
  bi.biYPelsPerMeter = 2; //we
  bi.biClrUsed = 3; //we ^^
  bi.biClrImportant = 4; //still we

  out.create(height, width, CV_8UC3);

  GetDIBits(memoryDeviceContext, bitmap, 0, height, out.getMatRef().data, (BITMAPINFO *) &bi, DIB_RGB_COLORS);
  // remove alpha channel
//  ::cv::cvtColor(out, out, cv::COLOR_BGRA2BGR);

  //clean up!
  DeleteObject(bitmap);
  DeleteDC(memoryDeviceContext); //delete not release!
  ReleaseDC(hWND, deviceContext);
}
#endif

std::vector<eb::Window> eb::Window::getSubWindows() {
  std::vector<eb::Window> rst;
  struct EnumChildWindowsGetSubWindowsParam param{
      &rst,
  };

  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  EnumChildWindows(this->getId(), enumChildWindowsGetSubWindows, reinterpret_cast<LPARAM>(&param));
  #endif
  return rst;
}


void eb::Window::refresh() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  if (this->getId() == nullptr) {
    return;
  }
  this->title = this->getTitle();

  RECT r;
  GetWindowRect(this->getId(), &r);
  this->_rect = rectWin2cv(r);

  TCHAR cName[MAX_PATH + 1];
  GetClassName(this->getId(), cName, _countof(cName));
  this->className = std::string(cName);
#endif

#ifdef __APPLE__
  CGWindowID ids[1] = {this->wid};
  CFArrayRef idArray = CFArrayCreate(nullptr, (const void **) ids, 1, nullptr);
  auto desc = CGWindowListCreateDescriptionFromArray(idArray);
//  std::cout << "desc length: " << CFArrayGetCount(desc) << std::endl;
  for (auto i = 0; i < CFArrayGetCount(desc); i++) {
    auto item = (CFDictionaryRef)CFArrayGetValueAtIndex(desc, i);
    if (CFDictionaryContainsKey(item, kCGWindowBounds)) {
      auto bounds = (CFDictionaryRef)CFDictionaryGetValue(item, kCGWindowBounds);
      CGRect _rect;
      CGRectMakeWithDictionaryRepresentation(bounds, &_rect);
      // how to get the bounds
//      std::cout << "bounds: " << _rect.origin << std::endl;
      this->_rect.x = (int)_rect.origin.x;
      this->_rect.y = (int)_rect.origin.y;
      this->_rect.width = (int)_rect.size.width;
      this->_rect.height = (int)_rect.size.height;
//      std::cout << "bounds: " << this->rect << std::endl;
    } else {
      std::cout << "no bounds" << std::endl;
    }
  }
  CFRelease(desc);
  CFRelease(idArray);
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
  // error C2662: “HWND eb::Window::getId(void)”: 不能将“this”指针从“const eb::Window”转换为“eb::Window &”
  return this->getId() == GetAncestor(this->getId(), GA_ROOT);
#endif
  return false;
}

std::string eb::Window::str() const {
  return "Window("
         "title: " + this->title
         + ", rect: " + eb::to_string(this->_rect)
         + ", enable: " + std::to_string(this->isEnable())
         + ")";
}

bool eb::Window::isCloaked() const {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  BOOL isCloaked = FALSE;
  return SUCCEEDED(DwmGetWindowAttribute(this->getId(), DWMWA_CLOAKED,
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
  if (this->_rect.width == 0 || this->_rect.height == 0) {
    return false;
  }
  return !IsIconic(getId()) && IsWindowVisible(getId());
#endif
  return false;
}

std::string eb::Window::getTitle() {
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  auto len = GetWindowTextLength(getId());
  auto pszMem = (PSTR) VirtualAlloc((LPVOID) NULL,
                                    (DWORD) (len + 1), MEM_COMMIT,
                                    PAGE_READWRITE);
  GetWindowText(getId(), pszMem,
                len + 1);
  auto rst = std::string(pszMem);
  VirtualFree(pszMem, (DWORD) (len + 1), MEM_DECOMMIT);
  return rst;
  #endif
  return "";
}

void eb::Window::screenshot(const cv::_OutputArray &output, int scale) {
  this->refresh();
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  getMat(getId(), output, scale);
  #else
  auto imgRef = CGWindowListCreateImage(CGRect{
    (double)_rect.x, (double)_rect.y, (double)_rect.width, (double)_rect.height},
                                        kCGWindowListOptionIncludingWindow | kCGWindowListExcludeDesktopElements,
//                                        kCGWindowListOptionOnScreenOnly,
                                        this->wid, kCGWindowImageDefault);
  CGColorSpaceRef colorSpace = CGImageGetColorSpace(imgRef);

  // width: 2880
  // height: 1800
  // 系统也是这么大
  // why 1600 and 1256??
  auto width = CGImageGetWidth(imgRef) / 2;
  auto height = CGImageGetHeight(imgRef) / 2;
  std::cout << "width: " << width << "height: " << height << std::endl;
  output.create(height, width, CV_8UC4);

  CGContextRef contextRef = CGBitmapContextCreate(output.getMatRef().data,                 // Pointer to backing data
                                                  width,                      // Width of bitmap
                                                  height,                     // Height of bitmap
                                                  8,                          // Bits per component
                                                  output.getMatRef().step[0],              // Bytes per row
                                                  colorSpace,                 // Colorspace
                                                  kCGImageAlphaNoneSkipLast |
                                                      kCGBitmapByteOrderDefault); // Bitmap info flags

  CGContextDrawImage(contextRef, CGRectMake(0, 0, width, height), imgRef);
  CGContextRelease(contextRef);
  CGImageRelease(imgRef);

  cv::cvtColor(output, output, cv::COLOR_RGB2BGR);
  #endif
}

std::ostream &eb::operator<<(std::ostream &out, const eb::Window &window) {
  out << window.str();
  return out;
}

bool eb::Window::isVisible() {
  this->refresh();
  return this->_rect.width > 0 && this->_rect.height > 0;
}

eb::Window::Window(wid_t _wid): wid(_wid), title(""),  className("") {
//  this->refresh();
}

wid_t eb::Window::getId() const {
  return this->wid;
}

#ifdef __APPLE__
/**
 * Converts a CFString to a UTF-8 std::string if possible.
 *
 * @param input A reference to the CFString to convert.
 * @return Returns a std::string containing the contents of CFString converted to UTF-8. Returns
 *  an empty string if the input reference is null or conversion is not possible.
 */
static std::string cfStringToStdString(CFStringRef input)
{
  if (!input)
    return {};

  // Attempt to access the underlying buffer directly. This only works if no conversion or
  //  internal allocation is required.
  auto originalBuffer{ CFStringGetCStringPtr(input, kCFStringEncodingUTF8) };
  if (originalBuffer)
    return originalBuffer;

  // Copy the data out to a local buffer.
  auto lengthInUtf16{ CFStringGetLength(input) };
  auto maxLengthInUtf8{ CFStringGetMaximumSizeForEncoding(lengthInUtf16,
                                                          kCFStringEncodingUTF8) + 1 }; // <-- leave room for null terminator
  std::vector<char> localBuffer(maxLengthInUtf8);

  if (CFStringGetCString(input, localBuffer.data(), maxLengthInUtf8, maxLengthInUtf8))
    return localBuffer.data();

  return {};
}
#endif

void eb::Window::printAllWindow() {
#ifdef __APPLE__
  auto windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
//  std::cout << "pid: " << this->pid << std::endl;
  for (auto i = 0; i < CFArrayGetCount(windowList); i++) {
    // how to do?
    std::cout << "Window: ";
    auto item = (CFDictionaryRef)CFArrayGetValueAtIndex(windowList, i);
    pid_t _pid;
    CFNumberGetValue((CFNumberRef)CFDictionaryGetValue(item, kCGWindowOwnerPID),
                     kCFNumberSInt32Type, &_pid);
    CGWindowID wid;
    CFNumberGetValue((CFNumberRef)CFDictionaryGetValue(item, kCGWindowNumber),
                     kCFNumberSInt32Type, &wid);
    std::cout << "id: " << wid;

    auto bounds = (CFDictionaryRef)CFDictionaryGetValue(item, kCGWindowBounds);
    CGRect _rect;
    CGRectMakeWithDictionaryRepresentation(bounds, &_rect);
    std::cout << ", bounds: (" << _rect.origin.x << ", " << _rect.origin.y << " " << _rect.size.width << "x" << _rect.size.height << ")";

    auto printStringItem = [](CFDictionaryRef item, const void *key, const std::string &_title) {
      if (CFDictionaryContainsKey(item, key)) {
        std::cout << ", " << _title << ": ";
        auto value = (CFStringRef)CFDictionaryGetValue(item, key);
        char buffer[1024];
        const char *ptr = CFStringGetCStringPtr(value, kCFStringEncodingMacRoman);
        if (ptr) {
          std::cout << ptr;
        } else {
          std::cout << "no string";
        };
//        std::cout << cfStringToStdString(value) << std::endl;
      }
    };

    printStringItem(item, kCGWindowName, "windowName");
    printStringItem(item, kCGWindowOwnerName, "windowOwnerName");

    std::cout << std::endl;
  }
  CFRelease(windowList);
#endif
}

bool eb::Window::findWindow(eb::Window *out, const std::string &processName, std::string windowName) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
//  auto thSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//  if (!thSnap) {
//    return nullptr;
//  }
//  PROCESSENTRY32 pe;
//
//  // need close pe?
//  if (!Process32Next(thSnap, &pe)) {
//    return nullptr;
//  }
//
//  const bool ignoreName = processName.empty();
//
//  HWND rst = nullptr;
//  do {
//    if (ignoreName || processName == pe.szExeFile) {
//      // ok, we find the process
//      // but how can we get the window?
//      struct ParamEnumFindWindow param{
//          pe.th32ProcessID,
//          &windowName,
//          &rst
//      };
//      EnumWindows(enumFindWindow, reinterpret_cast<LPARAM>(&param));
//    }
//  } while (Process32Next(thSnap, &pe));
//
//  CloseHandle(thSnap);
  // right that use this tec??
#endif
  return false;
}
bool eb::Window::findWindow(eb::Window *out, const std::string &windowName) {
  return false;
}

bool eb::Window::isImeStaff() const {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
//  std::cout << "title: " << this->title << ", this->title == TITLE_MSCTFIME_UI: " << (this->title == TITLE_MSCTFIME_UI) << std::endl;
  return this->title == TITLE_MSCTFIME_UI || this->title == TITLE_DEFAULT_IME;
#else
    return false;
#endif
}

cv::Rect2i eb::Window::rect(bool forceRefresh) {
  if (forceRefresh || this->_rect.width == 0 || this->_rect.height == 0) {
    this->refresh();
  }
  return this->_rect;
}

bool eb::Window::isNormalWindow() {
  return this->isEnable() && this->isVisible() && !this->isImeStaff();
}

bool eb::Window::isEnable() const {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  return IsWindowEnabled(this->wid);
#else
  return true;
#endif
}
