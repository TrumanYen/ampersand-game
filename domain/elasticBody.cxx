#include <domain/elasticBody.h>

#include <algorithm>
#include <domain/mapState.h>

namespace {
const double TERMINAL_VELOCITY = 20.0;
const double NEGATIVE_TERMINAL_VELOCITY = -1.0 * TERMINAL_VELOCITY;
const Vector2D<double> GRAVITY(0.0, 9.81);
const double AIR_RESISTANCE_VELOCITY_MULTIPLIER = 0.995;
} // namespace

ElasticBody::ElasticBody(const MapState &mapState, double collisionCoefficient,
                         const Vector2D<double> &spawnPoint,
                         const Vector2D<double> &initialVelocity)
    : mapState_(mapState), collisionCoefficient_(collisionCoefficient),
      pos_(spawnPoint), vel_(initialVelocity), accel_(GRAVITY) {}

ElasticBody::~ElasticBody() = default;

void ElasticBody::accelerate(const Vector2D<double> &acceleration) {
  accel_ = accel_ + acceleration;
}

void ElasticBody::incrementTime(double timeSeconds) {
  Vector2D<double> newVelUnclamped =
      ((accel_ * timeSeconds) + vel_) * AIR_RESISTANCE_VELOCITY_MULTIPLIER;
  vel_.x = std::clamp(newVelUnclamped.x, NEGATIVE_TERMINAL_VELOCITY,
                      TERMINAL_VELOCITY);
  vel_.y = std::clamp(newVelUnclamped.y, NEGATIVE_TERMINAL_VELOCITY,
                      TERMINAL_VELOCITY);

  attemptDisplacement(vel_ * timeSeconds);

  accel_ = GRAVITY; // reset acceleration at the end of each frame
}

// for now we can assume the only collisions are the walls, and that all the
// walls except the floor are stationary.
void ElasticBody::attemptDisplacement(const Vector2D<double> &displacement) {
  Vector2D<double> desiredPos = pos_ + displacement;

  bool horizontalCollisionDetected =
      (desiredPos.x < 0.0 || desiredPos.x > mapState_.mapWidthMeters());
  bool ceilingCollisionDetected = desiredPos.y < 0.0;
  bool floorCollisionDetected = desiredPos.y > mapState_.mapHeightMeters();

  pos_.x = std::clamp(desiredPos.x, 0.0, mapState_.mapWidthMeters());
  pos_.y = std::clamp(desiredPos.y, 0.0, mapState_.mapHeightMeters());

  if (horizontalCollisionDetected) {
    vel_.x *= (-0.9 * collisionCoefficient_);
    vel_.y *= collisionCoefficient_;
  }
  if (floorCollisionDetected) {
    vel_.y -= mapState_.floorVelocity();
  }
  if (ceilingCollisionDetected || floorCollisionDetected) {
    vel_.y *= (-0.9 * collisionCoefficient_);
    vel_.x *= collisionCoefficient_;
  }
}

void ElasticBody::setVelocity(const Vector2D<double> &velocity) {
  vel_ = velocity;
}

const Vector2D<double> &ElasticBody::position() const { return pos_; }

const Vector2D<double> &ElasticBody::velocity() const { return vel_; }
