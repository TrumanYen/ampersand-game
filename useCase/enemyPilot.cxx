#include <useCase/enemyPilot.h>

#include <cmath>
#include <domain/ampersandSimulation.h>
#include <domain/thrusterState.h>

EnemyPilot::EnemyPilot(const AmpersandSimulation &playerAmpersand,
                       AmpersandSimulation &enemyAmpersand)
    : playerAmpersand_(playerAmpersand), enemyAmpersand_(enemyAmpersand) {}

EnemyPilot::~EnemyPilot() = default;

void EnemyPilot::update() {
  std::pair<double, double> playerLocation = playerAmpersand_.currentPos();
  std::pair<double, double> enemyLocation = enemyAmpersand_.currentPos();

  double errorX = enemyLocation.first - playerLocation.first;
  double errorY = enemyLocation.second - playerLocation.second;
  // World's most naiive control loop.  Surprisingly works kind of ok.
  bool shouldMoveHorizontally = (std::abs(errorX) >= std::abs(errorY));
  if (shouldMoveHorizontally) {
    if (errorX > 0) {
      enemyAmpersand_.setThrusterState(ThrusterState::Left);
    } else {
      enemyAmpersand_.setThrusterState(ThrusterState::Right);
    }
  } else {
    if (errorY > 0) {
      enemyAmpersand_.setThrusterState(ThrusterState::Up);
    } else {
      enemyAmpersand_.setThrusterState(ThrusterState::Down);
    }
  }
}
