#pragma once

#include <memory>

class MapState;
class AmpersandSimulation;

class SimulationDomain {
public:
  SimulationDomain();
  ~SimulationDomain();

  void incrementTime(double timeDeltaSeconds);
  MapState &mapState();
  AmpersandSimulation &ampersandSim();
  AmpersandSimulation &enemyAmpersandSim();

private:
  std::unique_ptr<MapState> mapState_;
  std::unique_ptr<AmpersandSimulation> ampersandSim_;
  std::unique_ptr<AmpersandSimulation> enemyAmpersandSim_;
};
