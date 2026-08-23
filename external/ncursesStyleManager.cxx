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
  init_pair(4, COLOR_WHITE, COLOR_RED);
  colorToStyleMap_[TuiColor::WhiteOnRed] = COLOR_PAIR(4);
  init_pair(5, COLOR_WHITE, -1);
  colorToStyleMap_[TuiColor::Transparent] = COLOR_PAIR(5);
}

NcursesStyleManager::~NcursesStyleManager() = default;

chtype NcursesStyleManager::styleWithColor(TuiColor color) {
  if (colorToStyleMap_.contains(color)) {
    return colorToStyleMap_[color];
  }
  return colorToStyleMap_[TuiColor::Blue];
}
