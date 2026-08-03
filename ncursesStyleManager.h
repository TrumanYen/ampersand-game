#pragma once

#include <ncurses.h>

class NcursesStyleManager {
public:
  NcursesStyleManager();
  ~NcursesStyleManager();

  chtype red() const;
  chtype green() const;
  chtype blue() const;

private:
  chtype red_;
  chtype green_;
  chtype blue_;
};
