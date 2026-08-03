#include <ncursesStyleManager.h>

#include <ncurses.h>

NcursesStyleManager::NcursesStyleManager() {
  start_color();
  use_default_colors();

  init_pair(1, COLOR_RED, -1);
  red_ = COLOR_PAIR(1);
  init_pair(2, COLOR_GREEN, -1);
  green_ = COLOR_PAIR(2);
  init_pair(3, COLOR_BLUE, -1);
  blue_ = COLOR_PAIR(3);
}

NcursesStyleManager::~NcursesStyleManager() = default;

chtype NcursesStyleManager::red() const { return red_; }

chtype NcursesStyleManager::green() const { return green_; }

chtype NcursesStyleManager::blue() const { return blue_; }
