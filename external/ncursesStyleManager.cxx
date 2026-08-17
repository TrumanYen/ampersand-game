#include <external/ncursesStyleManager.h>

#include <ncurses.h>

NcursesStyleManager::NcursesStyleManager() {
  start_color();
  use_default_colors();

  init_pair(1, COLOR_RED, -1);
  colorToStyleMap_[TuiColor::Red] = COLOR_PAIR(1);
  init_pair(2, COLOR_GREEN, -1);
  colorToStyleMap_[TuiColor::Green] = COLOR_PAIR(2);
  init_pair(3, COLOR_BLUE, -1);
  colorToStyleMap_[TuiColor::Blue] = COLOR_PAIR(3);
}

NcursesStyleManager::~NcursesStyleManager() = default;

chtype NcursesStyleManager::styleWithColor(TuiColor color) {
  if (colorToStyleMap_.contains(color)) {
    return colorToStyleMap_[color];
  }
  return colorToStyleMap_[TuiColor::Blue];
}
