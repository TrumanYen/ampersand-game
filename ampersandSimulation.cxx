#include <ampersandSimulation.h>

#include <algorithm>
#include <cmath>
#include <mapState.h>

namespace {
const double THRUSTER_ACCEL_MPSS = 15.0;
const double TERMINAL_VELOCITY = 20.0;
const double NEGATIVE_TERMINAL_VELOCITY = -1.0 * TERMINAL_VELOCITY;

} // namespace

AmpersandSimulation::AmpersandSimulation(const MapState &mapState)
    : mapState_(mapState), xPos_(0.0), yPos_(0.0), xVel_(0.0), yVel_(0.0),
      xAccel_(0.0), yAccel_(0.0), thrusterState_(ThrusterState::Off) {}

AmpersandSimulation::~AmpersandSimulation() = default;

void AmpersandSimulation::incrementTime(double timeSeconds) {
  calculateCurrentAcceleration();

  double deltaVelX = xAccel_ * timeSeconds;
  double deltaVelY = yAccel_ * timeSeconds;
  xVel_ = std::clamp(xVel_ + deltaVelX, NEGATIVE_TERMINAL_VELOCITY,
                     TERMINAL_VELOCITY);
  yVel_ = std::clamp(yVel_ + deltaVelY, NEGATIVE_TERMINAL_VELOCITY,
                     TERMINAL_VELOCITY);

  double deltaX = xVel_ * timeSeconds;
  double deltaY = yVel_ * timeSeconds;

  displaceAmpersand(deltaX, deltaY);
}

void AmpersandSimulation::setThrusterState(ThrusterState state) {
  thrusterState_ = state;
}

std::pair<double, double> AmpersandSimulation::currentPos() const {
  return std::pair<double, double>(xPos_, yPos_);
}

std::pair<double, double> AmpersandSimulation::currentVel() const {
  return std::pair<double, double>(xVel_, yVel_);
}

std::pair<double, double> AmpersandSimulation::currentAccel() const {
  return std::pair<double, double>(xAccel_, yAccel_);
}

ThrusterState AmpersandSimulation::currentThrusterState() const {
  return thrusterState_;
}

void AmpersandSimulation::displaceAmpersand(double deltaX, double deltaY) {
  // for now we can assume the only collisions are the walls, and that all the
  // walls except the floor are stationary.
  double desiredXPos = xPos_ + deltaX;
  double desiredYPos = yPos_ + deltaY;

  bool horizontalCollisionDetected =
      (desiredXPos < 0.0 || desiredXPos > mapState_.mapWidthMeters());
  bool ceilingCollisionDetected = desiredYPos < 0.0;
  bool floorCollisionDetected = desiredYPos > mapState_.mapHeightMeters();

  xPos_ = std::clamp(desiredXPos, 0.0, mapState_.mapWidthMeters());
  yPos_ = std::clamp(desiredYPos, 0.0, mapState_.mapHeightMeters());

  if (horizontalCollisionDetected) {
    xVel_ = -0.8 * xVel_;
    yVel_ = 0.9 * yVel_;
  }
  if (floorCollisionDetected) {
    yVel_ -= mapState_.floorVelocity();
  }
  if (ceilingCollisionDetected || floorCollisionDetected) {
    yVel_ = -0.8 * yVel_;
    xVel_ = 0.9 * xVel_;
  }
}

void AmpersandSimulation::calculateCurrentAcceleration() {
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
