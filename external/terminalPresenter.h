#pragma once

#include <memory>
#include <ncurses.h>
#include <utility>

class NcursesStyleManager;
enum class ThrusterState;
class ViewModel;

class TerminalPresenter {
public:
  TerminalPresenter(ViewModel &viewModel);
  ~TerminalPresenter();

  void run();

private:
  void handleKeyPresses();
  void drawAmpersand(std::pair<int, int> location, ThrusterState thrusterState,
                     chtype style);

private:
  ViewModel &viewModel_;
  bool running_;
  int lastCharReadFromBuffer_;

  std::unique_ptr<NcursesStyleManager> styles_;
};
