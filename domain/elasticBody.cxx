#include <domain/elasticBody.h>

#include <algorithm>
#include <domain/mapState.h>

namespace {
const double TERMINAL_VELOCITY = 20.0;
const double NEGATIVE_TERMINAL_VELOCITY = -1.0 * TERMINAL_VELOCITY;
const Vector2D<double> GRAVITY(0.0, 9.81);
const double AIR_RESISTANCE_VELOCITY_MULTIPLIER = 0.995;
} // namespace

ElasticBody::ElasticBody(const MapState &mapState, Vector2D<double> spawnPoint)
    : mapState_(mapState), pos_(spawnPoint), vel_(0.0, 0.0), accel_(GRAVITY) {}

ElasticBody::~ElasticBody() = default;

void ElasticBody::accelerate(Vector2D<double> acceleration) {
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
void ElasticBody::attemptDisplacement(Vector2D<double> displacement) {
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

void ElasticBody::setVelocity(Vector2D<double> velocity) { vel_ = velocity; }

Vector2D<double> ElasticBody::position() const { return pos_; }

Vector2D<double> ElasticBody::velocity() const { return vel_; }
