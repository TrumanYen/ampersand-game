#pragma once

#include <memory>

class ElasticBody;
class MapState;

class SimulationDomain {
public:
  SimulationDomain();
  ~SimulationDomain();

  bool bodiesHaveCollided() const;

  void incrementTime(double timeDeltaSeconds);
  MapState &mapState();
  ElasticBody &collidableBodyA();
  ElasticBody &collidableBodyB();

private:
  std::unique_ptr<MapState> mapState_;
  std::unique_ptr<ElasticBody> collidableBodyA_;
  std::unique_ptr<ElasticBody> collidableBodyB_;
};
