#include <useCase/enemyPilot.h>

#include <cmath>
#include <domain/mapState.h>
#include <useCase/ampersand.h>
#include <useCase/thrusterState.h>

namespace {
const double POSITIVE_DELTA_ERROR_CUTOFF = 3.0;
const double NEGATIVE_DELTA_ERROR_CUTOFF = -1.0 * POSITIVE_DELTA_ERROR_CUTOFF;
const double GRAVITY_BIAS = 0.5;
} // namespace

EnemyPilot::EnemyPilot(const Ampersand &playerAmpersand,
                       Ampersand &enemyAmpersand, const MapState &mapState)
    : playerAmpersand_(playerAmpersand), enemyAmpersand_(enemyAmpersand),
      previousError_(0.0, 0.0), mapState_(mapState) {}

EnemyPilot::~EnemyPilot() = default;

void EnemyPilot::update(double secondsElapsed) {
  if (secondsElapsed <= 0.0) {
    return;
  }
  Vector2D<double> error =
      enemyAmpersand_.currentPosition() - playerAmpersand_.currentPosition();

  Vector2D<double> deltaError = error - previousError_;
  previousError_ = error;
  Vector2D<double> deltaErrorOverTime = deltaError / secondsElapsed;

  bool playerIsRestingOnFloor =
      (playerAmpersand_.currentPosition().y >= mapState_.mapHeightMeters());
  if (!playerIsRestingOnFloor) {
    error.y += GRAVITY_BIAS;
  }
  double errorXMag = std::abs(error.x);
  double errorYMag = std::abs(error.y);
  // because we can only fire the thruster in one direction at a time, we
  // need to prioritize the axis with the most error.
  bool shouldMoveHorizontally = (errorXMag > errorYMag);
  ThrusterState thrusterState = ThrusterState::Off;
  if (shouldMoveHorizontally) {
    if (error.x > 0) {
      if (deltaErrorOverTime.x > NEGATIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Left;
      }
    } else {
      if (deltaErrorOverTime.x < POSITIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Right;
      }
    }
  } else {
    if (error.y > 0) {
      if (deltaErrorOverTime.y > NEGATIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Up;
      }
    } else {
      if (deltaErrorOverTime.y < POSITIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Down;
      }
    }
  }
  enemyAmpersand_.setThrusterState(thrusterState);
}
