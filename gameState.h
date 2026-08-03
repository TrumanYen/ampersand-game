#pragma once

#include <memory>

class MapState;
class AmpersandSimulation;

class GameState {
public:
  GameState();
  ~GameState();

  void incrementTimeMs(double timeDeltaMs);
  MapState &mapState();
  AmpersandSimulation &ampersandSim();
  AmpersandSimulation &enemyAmpersandSim();

private:
  std::unique_ptr<MapState> mapState_;
  std::unique_ptr<AmpersandSimulation> ampersandSim_;
  std::unique_ptr<AmpersandSimulation> enemyAmpersandSim_;
};
