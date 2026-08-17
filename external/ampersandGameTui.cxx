#include <external/ampersandGameTui.h>

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

AmpersandGameTui::AmpersandGameTui(ViewModel &viewModel)
    : viewModel_(viewModel) {
  initscr();
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  styles_ = std::make_unique<NcursesStyleManager>();
  running_ = false;
}

AmpersandGameTui::~AmpersandGameTui() {}

void AmpersandGameTui::run() {
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

    for (const TuiCell &cell : viewModel_.cellsToRender()) {
      mvaddch(cell.location.y, cell.location.x,
              cell.character | styles_->styleWithColor(cell.color));
    }

    if (viewModel_.gameOver()) {
      break;
    }
    refresh();
    // Quick and dirty timing loop.  Should thread properly later
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_PERIOD_MS));
  }

  endwin();
}

void AmpersandGameTui::handleKeyPresses() {
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
