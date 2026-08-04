#include <external/terminalPresenter.h>

#include <adapter/viewModel.h>
#include <chrono>
#include <domain/thrusterState.h>
#include <external/ncursesStyleManager.h>
#include <thread>

namespace {
const int TARGET_FPS = 60;
const int FRAME_PERIOD_MS = 1000 / TARGET_FPS;
const int TARGET_KEYPRESS_CAPTURE_FREQ = 10;
const int FRAMES_PER_KEYPRESS_READ = TARGET_FPS / TARGET_KEYPRESS_CAPTURE_FREQ;
} // namespace

TerminalPresenter::TerminalPresenter(ViewModel &viewModel)
    : viewModel_(viewModel) {
  initscr();
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  styles_ = std::make_unique<NcursesStyleManager>();
  running_ = false;
}

TerminalPresenter::~TerminalPresenter() {}

void TerminalPresenter::run() {
  viewModel_.updateTerminalDimensions(COLS, LINES);
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
    viewModel_.incrementTimeMs(FRAME_PERIOD_MS);
    erase();
    drawAmpersand(viewModel_.currentPositionCharsXY(),
                  viewModel_.currentThrusterState(), styles_->green());
    drawAmpersand(viewModel_.enemyCurrentPositionCharsXY(),
                  viewModel_.enemyCurrentThrusterState(), styles_->red());
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
      viewModel_.updateTerminalDimensions(COLS, LINES);
    default:
      break;
    }
  } while (lastCharReadFromBuffer_ != ERR);
  viewModel_.setThrusterState(commandedThrusterState);
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
