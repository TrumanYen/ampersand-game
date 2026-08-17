#include <domain/ampersandSimulation.h>

#include <algorithm>
#include <cmath>
#include <domain/mapState.h>
#include <domain/thrusterState.h>

namespace {
const double THRUSTER_ACCEL_MPSS = 15.0;
const double TERMINAL_VELOCITY = 20.0;
const double NEGATIVE_TERMINAL_VELOCITY = -1.0 * TERMINAL_VELOCITY;

} // namespace

AmpersandSimulation::AmpersandSimulation(const MapState &mapState,
                                         Vector2D<double> spawnPoint)
    : mapState_(mapState), pos_(spawnPoint), vel_(0.0, 0.0),
      thrusterState_(ThrusterState::Off) {}

AmpersandSimulation::~AmpersandSimulation() = default;

void AmpersandSimulation::incrementTime(double timeSeconds) {
  Vector2D<double> newVelUnclamped =
      (currentAcceleration() * timeSeconds) + vel_;
  vel_.x = std::clamp(newVelUnclamped.x, NEGATIVE_TERMINAL_VELOCITY,
                      TERMINAL_VELOCITY);
  vel_.y = std::clamp(newVelUnclamped.y, NEGATIVE_TERMINAL_VELOCITY,
                      TERMINAL_VELOCITY);

  displaceAmpersand(vel_ * timeSeconds);
}

void AmpersandSimulation::setThrusterState(ThrusterState state) {
  thrusterState_ = state;
}

Vector2D<double> AmpersandSimulation::currentPos() const { return pos_; }

Vector2D<double> AmpersandSimulation::currentVel() const { return vel_; }

ThrusterState AmpersandSimulation::currentThrusterState() const {
  return thrusterState_;
}

void AmpersandSimulation::displaceAmpersand(Vector2D<double> displacement) {
  // for now we can assume the only collisions are the walls, and that all the
  // walls except the floor are stationary.
  Vector2D<double> desiredPos = pos_ + displacement;

  bool horizontalCollisionDetected =
      (desiredPos.x < 0.0 || desiredPos.x > mapState_.mapWidthMeters());
  bool ceilingCollisionDetected = desiredPos.y < 0.0;
  bool floorCollisionDetected = desiredPos.y > mapState_.mapHeightMeters();

  pos_.x = std::clamp(desiredPos.x, 0.0, mapState_.mapWidthMeters());
  pos_.y = std::clamp(desiredPos.y, 0.0, mapState_.mapHeightMeters());

  if (horizontalCollisionDetected) {
    vel_.x *= -0.8;
    vel_.y *= 0.9;
  }
  if (floorCollisionDetected) {
    vel_.y -= mapState_.floorVelocity();
  }
  if (ceilingCollisionDetected || floorCollisionDetected) {
    vel_.y *= -0.8;
    vel_.x *= 0.9;
  }
}

Vector2D<double> AmpersandSimulation::currentAcceleration() const {
  Vector2D<double> accel(0.0, 9.81);
  switch (thrusterState_) {
  case ThrusterState::Up:
    accel.y -= THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Down:
    accel.y += THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Left:
    accel.x -= THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Right:
    accel.x += THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Off:
  default:
    break;
  }
  return accel;
}
