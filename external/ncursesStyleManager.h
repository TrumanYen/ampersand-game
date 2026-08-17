#pragma once

#include <ncurses.h>

#include <adapter/tuiCell.h>
#include <map>

class NcursesStyleManager {
public:
  NcursesStyleManager();
  ~NcursesStyleManager();

  chtype styleWithColor(TuiColor color);

private:
  std::map<TuiColor, chtype> colorToStyleMap_;
};
