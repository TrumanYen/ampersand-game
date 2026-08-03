#include <terminalPresenter.h>

#include <algorithm>
#include <chrono>
#include <gameLogicContainer.h>
#include <ncurses.h>
#include <simToTerminalScaler.h>
#include <simulation.h>
#include <thread>

#define TRANSPARENT_BLUE_PAIR 1

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
  start_color();
  use_default_colors();
  init_pair(TRANSPARENT_BLUE_PAIR, COLOR_BLUE, -1);
  // Unfortunately need to instantiate this container here for now because we do
  // not yet have the ability to dynamically resize, so we need to receive the
  // aspect ratio on construction
  container_ = std::make_unique<GameLogicContainer>(COLS, LINES);
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
    container_->sim().incrementTimeMs(FRAME_PERIOD_MS);
    erase();
    drawAmpersand();
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
  container_->sim().setThrusterState(commandedThrusterState);
}

void TerminalPresenter::drawAmpersand() {
  std::pair<int, int> currentPosition =
      container_->simScaler().currentPositionCharsXY();
  ThrusterState currentThrusterState = container_->sim().currentThrusterState();

  mvaddch(currentPosition.second, currentPosition.first, '&');
  switch (currentThrusterState) {
  case ThrusterState::Left:
    mvaddch(currentPosition.second, currentPosition.first + 1,
            '<' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    mvaddch(currentPosition.second, currentPosition.first + 2,
            '<' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    break;
  case ThrusterState::Right:
    mvaddch(currentPosition.second, currentPosition.first - 1,
            '>' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    mvaddch(currentPosition.second, currentPosition.first - 2,
            '>' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    break;
  case ThrusterState::Down:
    mvaddch(currentPosition.second - 1, currentPosition.first,
            'v' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    mvaddch(currentPosition.second - 2, currentPosition.first,
            'v' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    break;
  case ThrusterState::Up:
    mvaddch(currentPosition.second + 1, currentPosition.first,
            '^' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    mvaddch(currentPosition.second + 2, currentPosition.first,
            '^' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    if (currentPosition.second + 2 >= LINES) {
      mvaddch(LINES - 1, currentPosition.first - 1,
              '>' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
      mvaddch(LINES - 1, currentPosition.first + 1,
              '<' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    }
    if (currentPosition.second + 1 >= LINES) {
      mvaddch(LINES - 1, currentPosition.first - 2,
              '>' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
      mvaddch(LINES - 1, currentPosition.first + 2,
              '<' | COLOR_PAIR(TRANSPARENT_BLUE_PAIR));
    }
    break;
  case ThrusterState::Off:
  default:
    break;
  }
}

void TerminalPresenter::drawStats() {
  std::pair<double, double> currentPos = container_->sim().currentPos();
  std::pair<double, double> currentVel = container_->sim().currentVel();
  std::pair<double, double> currentAccel = container_->sim().currentAccel();
  mvprintw(0, statsTextPosition_,
           "Pos: %.3f, %.3f    Vel: %.3f, %.3f   Accel: %.3f, %.3f",
           currentPos.first, currentPos.second, currentVel.first,
           currentVel.second, currentAccel.first, currentAccel.second);
}
