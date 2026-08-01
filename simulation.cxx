#include <simulation.h>

#include <algorithm>

Simulation::Simulation(int maxX, int maxY)
    : maxX_(maxX), maxY_(maxY), xPos_(0), yPos_(0) {}

Simulation::~Simulation() = default;

void Simulation::incrementPosition(int deltaX, int deltaY) {
  xPos_ += deltaX;
  yPos_ += deltaY;

  xPos_ = std::max(0, std::min(xPos_, maxX_));
  yPos_ = std::max(0, std::min(yPos_, maxY_));
}

std::pair<int, int> Simulation::currentPos() {
  return std::pair<int, int>(xPos_, yPos_);
}
