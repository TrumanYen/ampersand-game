#include <simulation.h>

Simulation::Simulation(int maxX, int maxY)
    : maxX_(maxX), maxY_(maxY), xPos_(0), yPos_(0) {}

Simulation::~Simulation() = default;

void Simulation::teleport(int deltaX, int deltaY) {
  xPos_ += deltaX;
  yPos_ += deltaY;
}

std::pair<int, int> Simulation::currentPos() {
  return std::pair<int, int>(xPos_, yPos_);
}
