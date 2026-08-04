#pragma once

#include <utility>

class AmpersandSimulation;

class EnemyPilot {
public:
  EnemyPilot(const AmpersandSimulation &playerAmpersand,
             AmpersandSimulation &enemyAmpersand);
  ~EnemyPilot();

  void update(double secondsElapsed);

private:
  const AmpersandSimulation &playerAmpersand_;
  AmpersandSimulation &enemyAmpersand_;

  std::pair<double, double> previousError_;
};
