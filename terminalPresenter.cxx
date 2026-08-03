#include <terminalPresenter.h>

#include <algorithm>
#include <ampersandSimulation.h>
#include <chrono>
#include <gameLogicContainer.h>
#include <gameState.h>
#include <ncursesStyleManager.h>
#include <simToTerminalScaler.h>
#include <thread>

namespace {
const int TARGET_FPS = 60;
const int FRAME_PERIOD_MS = 1000 / TARGET_FPS;
const int TARGET_KEYPRESS_CAPTURE_FREQ = 10;
const int FRAMES_PER_KEYPRESS_READ = TARGET_FPS / TARGET_KEYPRESS_CAPTURE_FREQ;
} // namespace

TerminalPresenter::TerminalPresenter() {
  initscr();
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  // Unfortunately need to instantiate this container here for now because we do
  // not yet have the ability to dynamically resize, so we need to receive the
  // aspect ratio on construction
  container_ = std::make_unique<GameLogicContainer>(COLS, LINES);
  styles_ = std::make_unique<NcursesStyleManager>();
  statsTextPosition_ = std::max(0, (COLS / 2) - 24);
  running_ = false;
}

TerminalPresenter::~TerminalPresenter() {}

void TerminalPresenter::run() {
  running_ = true;
  int framesSinceLastProcessedKeypresses = 0;

  while (running_) {
    // Should switch over to actually measuring key pressed and release events,
    // because this logic relies on the OS's key repeat rate being faster than
    // the FPS. This is why we're only processing keypresses every 6 frames
    if (framesSinceLastProcessedKeypresses >= FRAMES_PER_KEYPRESS_READ) {
      handleKeyPresses();
      framesSinceLastProcessedKeypresses = 0;
    } else {
      framesSinceLastProcessedKeypresses++;
    }
    container_->gameState().incrementTimeMs(FRAME_PERIOD_MS);
    erase();
    drawAmpersand(container_->simScaler().currentPositionCharsXY(),
                  container_->gameState().ampersandSim().currentThrusterState(),
                  styles_->green());
    drawAmpersand(
        container_->simScaler().enemyCurrentPositionCharsXY(),
        container_->gameState().enemyAmpersandSim().currentThrusterState(),
        styles_->red());
    drawStats();
    refresh();
    // Quick and dirty timing loop.  Should thread properly later
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_PERIOD_MS));
  }

  endwin();
}

void TerminalPresenter::handleKeyPresses() {
  // There may be many read from the buffer.  We should process all of them.
  ThrusterState commandedThrusterState = ThrusterState::Off;
  do {
    lastCharReadFromBuffer_ = getch();
    switch (lastCharReadFromBuffer_) {
    case 'h':
      commandedThrusterState = ThrusterState::Left;
      break;
    case 'l':
      commandedThrusterState = ThrusterState::Right;
      break;
    case 'j':
      commandedThrusterState = ThrusterState::Down;
      break;
    case 'k':
      commandedThrusterState = ThrusterState::Up;
      break;
    case 'q':
      running_ = false;
      break;
    case KEY_RESIZE:
      container_->simScaler().updateTerminalDimensions(COLS, LINES);
    default:
      break;
    }
  } while (lastCharReadFromBuffer_ != ERR);
  container_->gameState().ampersandSim().setThrusterState(
      commandedThrusterState);
}

void TerminalPresenter::drawAmpersand(std::pair<int, int> location,
                                      ThrusterState thrusterState,
                                      chtype style) {
  mvaddch(location.second, location.first, '&' | style);
  chtype blue = styles_->blue();
  switch (thrusterState) {
  case ThrusterState::Left:
    mvaddch(location.second, location.first + 1, '<' | blue);
    mvaddch(location.second, location.first + 2, '<' | blue);
    break;
  case ThrusterState::Right:
    mvaddch(location.second, location.first - 1, '>' | blue);
    mvaddch(location.second, location.first - 2, '>' | blue);
    break;
  case ThrusterState::Down:
    mvaddch(location.second - 1, location.first, 'v' | blue);
    mvaddch(location.second - 2, location.first, 'v' | blue);
    break;
  case ThrusterState::Up:
    mvaddch(location.second + 1, location.first, '^' | blue);
    mvaddch(location.second + 2, location.first, '^' | blue);
    if (location.second + 2 >= LINES) {
      mvaddch(LINES - 1, location.first - 1, '>' | blue);
      mvaddch(LINES - 1, location.first + 1, '<' | blue);
    }
    if (location.second + 1 >= LINES) {
      mvaddch(LINES - 1, location.first - 2, '>' | blue);
      mvaddch(LINES - 1, location.first + 2, '<' | blue);
    }
    break;
  case ThrusterState::Off:
  default:
    break;
  }
}

void TerminalPresenter::drawStats() {
  std::pair<double, double> currentPos =
      container_->gameState().ampersandSim().currentPos();
  std::pair<double, double> currentVel =
      container_->gameState().ampersandSim().currentVel();
  std::pair<double, double> currentAccel =
      container_->gameState().ampersandSim().currentAccel();
  mvprintw(0, statsTextPosition_,
           "Pos: %.3f, %.3f    Vel: %.3f, %.3f   Accel: %.3f, %.3f",
           currentPos.first, currentPos.second, currentVel.first,
           currentVel.second, currentAccel.first, currentAccel.second);
}
