#include <simulation.h>

#include <algorithm>
#include <cmath>

namespace {
static const double THRUSTER_ACCEL_MPSS = 15.0;
static const double TERMINAL_VELOCITY = 20.0;
static const double NEGATIVE_TERMINAL_VELOCITY = -1.0 * TERMINAL_VELOCITY;

} // namespace

Simulation::Simulation(double maxX, double maxY)
    : maxX_(maxX), maxY_(maxY), xPos_(0.0), yPos_(0.0), xVel_(0.0), yVel_(0.0),
      xAccel_(0.0), yAccel_(0.0) {}

Simulation::~Simulation() = default;

void Simulation::incrementTimeMs(double deltaMs) {
  calculateCurrentAcceleration();

  double deltaSeconds = 1e-3 * deltaMs;

  double deltaVelX = xAccel_ * deltaSeconds;
  double deltaVelY = yAccel_ * deltaSeconds;
  xVel_ = std::clamp(xVel_ + deltaVelX, NEGATIVE_TERMINAL_VELOCITY,
                     TERMINAL_VELOCITY);
  yVel_ = std::clamp(yVel_ + deltaVelY, NEGATIVE_TERMINAL_VELOCITY,
                     TERMINAL_VELOCITY);

  double deltaX = xVel_ * deltaSeconds;
  double deltaY = yVel_ * deltaSeconds;

  displaceAmpersand(deltaX, deltaY);
}

void Simulation::setThrusterState(ThrusterState state) {
  thrusterState_ = state;
}

std::pair<double, double> Simulation::currentPos() {
  return std::pair<double, double>(xPos_, yPos_);
}

std::pair<double, double> Simulation::currentVel() {
  return std::pair<double, double>(xVel_, yVel_);
}

std::pair<double, double> Simulation::currentAccel() {
  return std::pair<double, double>(xAccel_, yAccel_);
}

void Simulation::displaceAmpersand(double deltaX, double deltaY) {
  // for now we can assume the only collisions are the walls
  double desiredXPos = xPos_ + deltaX;
  double desiredYPos = yPos_ + deltaY;

  bool horizontalCollisionDetected = (desiredXPos < 0.0 || desiredXPos > maxX_);
  bool verticalCollisionDetected = (desiredYPos < 0.0 || desiredYPos > maxY_);

  xPos_ = std::clamp(desiredXPos, 0.0, maxX_);
  yPos_ = std::clamp(desiredYPos, 0.0, maxY_);

  if (horizontalCollisionDetected) {
    xVel_ = -0.8 * xVel_;
    yVel_ = 0.9 * yVel_;
  }
  if (verticalCollisionDetected) {
    yVel_ = -0.8 * yVel_;
    xVel_ = 0.9 * xVel_;
  }
}

void Simulation::calculateCurrentAcceleration() {
  // accel should not be a member variable since it gets recalculated every
  // frame anyways
  xAccel_ = 0.0;
  yAccel_ = 9.81;
  switch (thrusterState_) {
  case ThrusterState::Up:
    yAccel_ -= THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Down:
    yAccel_ += THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Left:
    xAccel_ -= THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Right:
    xAccel_ += THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Off:
  default:
    break;
  }
}
