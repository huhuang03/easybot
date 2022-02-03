//
// Created by huhua on 2021/10/5.
//

#include <gtest/gtest.h>
#include "./util_test.h"
#include <easybot/process.h>

TEST(ProcessTest, printAllProcess) {
  eb::Process::printAllProcess();
}

TEST(ProcessTest, testFindByName) {
//  auto h = startNotepad();
//  auto p = eb::Process::findByName("notepad.exe");
//  std::cout << p.getPid() << std::endl;
//  ASSERT_TRUE(p.getPid() > 0);
//  stopNotepad(h);
  // how to do this?
  auto pid = eb::Process::findPidByName("TextEdit");
  std::cout << "pid: " << pid << std::endl;
}

TEST(ProcessTest, testGetWindow) {
  auto p = eb::Process::findByName("TextEdit");
  auto wins = p.getWindows();
//  auto h = startNotepad();
//  auto p = eb::Process::findByName("notepad.exe");
//  auto windows = p.getWindows();
//  for (const auto &window : windows) {
//    std::cout << "window: " << window << ", visible: " << window.isTopLevel() << std::endl;
//  }
//  std::cout << windows.size() << std::endl;
//  ASSERT_TRUE(!windows.empty());
//  stopNotepad(h);
}


TEST(ProcessTest, testGetBiggestWindow) {
  auto p = eb::Process::findByName("TextEdit");
  auto win = p.getBiggestWindow();
  std::cout << win.getId() << std::endl;
//  auto h = startNotepad();
//  auto p = eb::Process::findByName("notepad.exe");
//  auto window = p.getBiggestWindow();
//  std::cout << "window: " << window << ", visible: " << window.isInScreen() << std::endl;
//  stopNotepad(h);
}
