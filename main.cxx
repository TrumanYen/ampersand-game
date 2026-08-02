#include <chrono>
#include <ncurses.h>
#include <simulation.h>
#include <thread>

int main() {
  const int TARGET_FPS = 60;
  const int FRAME_PERIOD_MS = 1000 / TARGET_FPS;
  const double ACCEL_CHARS_PER_MS = 0.003;

  initscr();
  nodelay(stdscr, TRUE);
  noecho();
  curs_set(0);

  int maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);
  Simulation sim(maxx - 1, maxy - 1);

  bool running = true;
  int inputchar;

  while (running) {
    inputchar = getch();
    switch (inputchar) {
    case 'h':
      sim.incrementVelocity(-1.0 * ACCEL_CHARS_PER_MS, 0.0);
      break;
    case 'l':
      sim.incrementVelocity(ACCEL_CHARS_PER_MS, 0.0);
      break;
    case 'j':
      sim.incrementVelocity(0.0, ACCEL_CHARS_PER_MS);
      break;
    case 'k':
      sim.incrementVelocity(0.0, -1.0 * ACCEL_CHARS_PER_MS);
      break;
    case 'q':
      running = false;
      break;
    default:
      break;
    }
    erase();
    sim.incrementTimeMs(FRAME_PERIOD_MS);
    // shhhh don't mind the implicit cast from double to int...
    std::pair<int, int> currentPosition = sim.currentPos();
    mvaddch(currentPosition.second, currentPosition.first, '@');
    refresh();
    // Quick and dirty timing loop.  Should thread properly later
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_PERIOD_MS));
  }

  endwin();

  return 0;
}
