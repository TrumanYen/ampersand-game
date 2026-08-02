#include <algorithm>
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
  int halfX = maxx / 2;
  int statsTextPosition =
      std::max(0, halfX - 24); // yes I counted the number of characters in the
                               // message and hard-coded it.
  ScaledSimulation scaledSim(maxx, maxy);
  Simulation &sim = scaledSim.sim();

  bool running = true;
  int inputchar;
  int mostRecentChar;
  int framesSinceLastProcessedKeypresses = 0;

  while (running) {
    // Should switch over to actually measuring key pressed and release events,
    // because this logic relies on the OS's key repeat rate being faster than
    // the FPS. This is why we're only processing keypresses every 6 frames
    if (framesSinceLastProcessedKeypresses >= 6) {
      mostRecentChar = ERR;
      while ((inputchar = getch()) != ERR) {
        // purge buffer and just get the most recent value
        mostRecentChar = inputchar;
      }
      switch (mostRecentChar) {
      case 'h':
        sim.setThrusterState(ThrusterState::Left);
        break;
      case 'l':
        sim.setThrusterState(ThrusterState::Right);
        break;
      case 'j':
        sim.setThrusterState(ThrusterState::Down);
        break;
      case 'k':
        sim.setThrusterState(ThrusterState::Up);
        break;
      case 'q':
        running = false;
        break;
      default:
        sim.setThrusterState(ThrusterState::Off);
        break;
      }
      framesSinceLastProcessedKeypresses = 0;
    } else {
      framesSinceLastProcessedKeypresses++;
    }
    erase();
    sim.incrementTimeMs(FRAME_PERIOD_MS);
    std::pair<int, int> currentPosition = scaledSim.currentPositionCharsXY();
    mvaddch(currentPosition.second, currentPosition.first, '@');
    std::pair<double, double> currentPos = sim.currentPos();
    std::pair<double, double> currentVel = sim.currentVel();
    std::pair<double, double> currentAccel = sim.currentAccel();
    mvprintw(0, statsTextPosition,
             "Pos: %.3f, %.3f    Vel: %.3f, %.3f   Accel: %.3f, %.3f",
             currentPos.first, currentPos.second, currentVel.first,
             currentVel.second, currentAccel.first, currentAccel.second);
    refresh();
    // Quick and dirty timing loop.  Should thread properly later
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_PERIOD_MS));
  }

  endwin();

  return 0;
}
