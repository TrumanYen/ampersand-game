#include <useCase/enemyPilot.h>

#include <cmath>
#include <domain/ampersandSimulation.h>
#include <domain/thrusterState.h>

namespace {
const double POSITIVE_DELTA_ERROR_CUTOFF = 3.0;
const double NEGATIVE_DELTA_ERROR_CUTOFF = -1.0 * POSITIVE_DELTA_ERROR_CUTOFF;

std::pair<double, double> operator-(std::pair<double, double> a,
                                    std::pair<double, double> b) {
  return std::pair<double, double>(a.first - b.first, a.second - b.second);
}

std::pair<double, double> operator/(std::pair<double, double> a, double b) {
  return std::pair<double, double>(a.first / b, a.second / b);
}
} // namespace

EnemyPilot::EnemyPilot(const AmpersandSimulation &playerAmpersand,
                       AmpersandSimulation &enemyAmpersand)
    : playerAmpersand_(playerAmpersand), enemyAmpersand_(enemyAmpersand) {}

EnemyPilot::~EnemyPilot() = default;

void EnemyPilot::update(double secondsElapsed) {
  std::pair<double, double> error =
      enemyAmpersand_.currentPos() - playerAmpersand_.currentPos();

  double errorXMag = std::abs(error.first);
  double errorYMag = std::abs(error.second);

  std::pair<double, double> deltaError = error - previousError_;
  previousError_ = error;
  std::pair<double, double> deltaErrorOverTime = deltaError / secondsElapsed;

  // because we can only fire the thruster in one direction at a time, we
  // need to prioritize the axis with the most error.
  bool shouldMoveHorizontally = (errorXMag > errorYMag);
  ThrusterState thrusterState = ThrusterState::Off;
  if (shouldMoveHorizontally) {
    if (error.first > 0) {
      if (deltaErrorOverTime.first > NEGATIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Left;
      }
    } else {
      if (deltaErrorOverTime.first < POSITIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Right;
      }
    }
  } else {
    if (error.second > 0) {
      // Maybe it's too hard to overshoot up anywyas? do we need this?
      if (deltaErrorOverTime.second > NEGATIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Up;
      }
    } else {
      if (deltaErrorOverTime.second < POSITIVE_DELTA_ERROR_CUTOFF) {
        thrusterState = ThrusterState::Down;
      }
    }
  }
  enemyAmpersand_.setThrusterState(thrusterState);
}
