#pragma once

class AmpersandSimulation;

class EnemyPilot {
public:
  EnemyPilot(const AmpersandSimulation& playerAmpersand, AmpersandSimulation& enemyAmpersand);
  ~EnemyPilot();

  void update();

private:
  const AmpersandSimulation &playerAmpersand_;
  AmpersandSimulation &enemyAmpersand_;
};
