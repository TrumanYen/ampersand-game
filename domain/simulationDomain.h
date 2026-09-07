#pragma once

#include <memory>

#include <domain/vector2d.h>

class ElasticBody;
class ElasticBodyRegistry;
class MapState;
class CollisionSimulator;

class SimulationDomain {
public:
  SimulationDomain();
  ~SimulationDomain();

  bool bodiesHaveCollided() const;
  const Vector2D<double> &avgVelocityBeforeCollision() const;
  double separationVelocityOfBodies() const;

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
