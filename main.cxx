#include <ncurses.h>
#include <simulation.h>
int main() {
  initscr();
  // nodelay(stdscr, TRUE);
  noecho();

  int maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);
  Simulation sim(maxx, maxy);

  bool running = true;
  int inputchar;

  while (running) {
    inputchar = getch();
    switch (inputchar) {
    case 'h':
      sim.teleport(-1, 0);
      break;
    case 'l':
      sim.teleport(1, 0);
      break;
    case 'j':
      sim.teleport(0, 1);
      break;
    case 'k':
      sim.teleport(0, -1);
      break;
    case 'q':
      running = false;
      break;
    default:
      printw("What even is that");
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
