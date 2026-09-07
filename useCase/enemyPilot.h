#pragma once

#include <toolkit/vector2d.h>

class Ampersand;
class MapState;

class EnemyPilot {
public:
  EnemyPilot(const Ampersand &playerAmpersand, Ampersand &enemyAmpersand,
             const MapState &mapState);
  ~EnemyPilot();

  void update(double secondsElapsed);

private:
  const Ampersand &playerAmpersand_;
  Ampersand &enemyAmpersand_;
  const MapState &mapState_;

  Vector2D<double> previousError_;
};
