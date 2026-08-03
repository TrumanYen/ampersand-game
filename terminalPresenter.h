#pragma once

#include <memory>

class GameLogicContainer;

class TerminalPresenter {
public:
  TerminalPresenter();
  ~TerminalPresenter();

  void run();

private:
  void handleKeyPresses();
  void drawAmpersand();
  void drawStats();

private:
  int statsTextPosition_;
  bool running_;
  int lastCharReadFromBuffer_;

  std::unique_ptr<GameLogicContainer> container_;
};
