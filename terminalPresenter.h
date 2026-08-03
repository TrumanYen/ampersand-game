#pragma once

#include <memory>
#include <utility>

class GameLogicContainer;
enum class ThrusterState;

class TerminalPresenter {
public:
  TerminalPresenter();
  ~TerminalPresenter();

  void run();

private:
  void handleKeyPresses();
  void drawAmpersand(
      std::pair<int, int> location, ThrusterState thrusterState,
      int color); // TODO: turn color into an enum or something more readable
  void drawStats();

private:
  int statsTextPosition_;
  bool running_;
  int lastCharReadFromBuffer_;

  std::unique_ptr<GameLogicContainer> container_;
};
