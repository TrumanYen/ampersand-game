#pragma once

#include <domain/vector2d.h>

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

  Vector2D<double> previousError_;
};
