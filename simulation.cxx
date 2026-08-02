#include <simulation.h>

#include <algorithm>

Simulation::Simulation(double maxX, double maxY)
    : maxX_(maxX), maxY_(maxY), xPos_(0), yPos_(0), xVel_(0), yVel_(0) {}

Simulation::~Simulation() = default;

void Simulation::incrementTimeMs(double deltaMs) {
  double deltaX = xVel_ * deltaMs;
  double deltaY = yVel_ * deltaMs;
  incrementPosition(deltaX, deltaY);
}

void Simulation::incrementVelocity(double deltaVelX, double deltaVelY) {
  xVel_ += deltaVelX;
  yVel_ += deltaVelY;
}

std::pair<double, double> Simulation::currentPos() {
  return std::pair<double, double>(xPos_, yPos_);
}

void Simulation::incrementPosition(double deltaX, double deltaY) {
  xPos_ += deltaX;
  yPos_ += deltaY;

  xPos_ = std::max(0.0, std::min(xPos_, maxX_));
  yPos_ = std::max(0.0, std::min(yPos_, maxY_));
}
