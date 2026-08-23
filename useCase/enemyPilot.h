#pragma once

#include <domain/vector2d.h>

class Ampersand;

class EnemyPilot {
public:
  EnemyPilot(const Ampersand &playerAmpersand, Ampersand &enemyAmpersand);
  ~EnemyPilot();

  void update(double secondsElapsed);

private:
  const Ampersand &playerAmpersand_;
  Ampersand &enemyAmpersand_;

  Vector2D<double> previousError_;
};
