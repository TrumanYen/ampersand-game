#include <ncurses.h>
#include <simulation.h>

int main() {
  initscr();
  // nodelay(stdscr, TRUE);
  noecho();

  int maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);
  Simulation sim(maxx - 1, maxy - 1);

  bool running = true;
  int inputchar;

  while (running) {
    inputchar = getch();
    switch (inputchar) {
    case 'h':
      sim.incrementPosition(-1, 0);
      break;
    case 'l':
      sim.incrementPosition(1, 0);
      break;
    case 'j':
      sim.incrementPosition(0, 1);
      break;
    case 'k':
      sim.incrementPosition(0, -1);
      break;
    case 'q':
      running = false;
      break;
    default:
      break;
    }
    erase();
    std::pair<int, int> currentPosition = sim.currentPos();
    mvaddch(currentPosition.second, currentPosition.first, '@');
    refresh();
  }

  endwin();

  return 0;
}
