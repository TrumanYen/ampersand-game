#pragma once

#include <memory>

class ElasticBody;
class ElasticBodyRegistry;
class MapState;
class CollisionSimulator;

class SimulationDomain {
public:
  SimulationDomain();
  ~SimulationDomain();

  bool bodiesHaveCollided() const;

  void incrementTime(double timeDeltaSeconds);
  MapState &mapState();
  ElasticBodyRegistry &elasticBodyRegistry();
  ElasticBody &collidableBodyA();
  ElasticBody &collidableBodyB();

private:
  std::unique_ptr<MapState> mapState_;
  std::unique_ptr<ElasticBodyRegistry> elasticBodyRegistry_;
  std::unique_ptr<ElasticBody> collidableBodyA_;
  std::unique_ptr<ElasticBody> collidableBodyB_;
  std::unique_ptr<CollisionSimulator> collisionSim_;
};
