#include <chrono>
#include <ncurses.h>
#include <scaledSimulation.h>
#include <thread>

int main() {
  const int TARGET_FPS = 60;
  const int FRAME_PERIOD_MS = 1000 / TARGET_FPS;

  initscr();
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);

  int maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);
  ScaledSimulation sim(maxx, maxy);

  bool running = true;
  int inputchar;

  while (running) {
    inputchar = getch();
    switch (inputchar) {
    case 'h':
      sim.accelerate(Direction::Left);
      break;
    case 'l':
      sim.accelerate(Direction::Right);
      break;
    case 'j':
      sim.accelerate(Direction::Down);
      break;
    case 'k':
      sim.accelerate(Direction::Up);
      break;
    case 'q':
      running = false;
      break;
    default:
      break;
    }
    erase();
    sim.incrementTimeMs(FRAME_PERIOD_MS);
    std::pair<int, int> currentPosition = sim.currentPositionCharsXY();
    mvaddch(currentPosition.second, currentPosition.first, '@');
    refresh();
    // Quick and dirty timing loop.  Should thread properly later
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_PERIOD_MS));
  }

  endwin();

  return 0;
}
