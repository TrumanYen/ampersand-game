#pragma once

#include <memory>
#include <ncurses.h>
#include <utility>

class GameLogicContainer;
class NcursesStyleManager;
enum class ThrusterState;

class TerminalPresenter {
public:
  TerminalPresenter();
  ~TerminalPresenter();

  void run();

private:
  void handleKeyPresses();
  void drawAmpersand(std::pair<int, int> location, ThrusterState thrusterState,
                     chtype style);
  void drawStats();

private:
  int statsTextPosition_;
  bool running_;
  int lastCharReadFromBuffer_;

  std::unique_ptr<GameLogicContainer> container_;
  std::unique_ptr<NcursesStyleManager> styles_;
};
