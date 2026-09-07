#pragma once

#include <toolkit/vector2d.h>

class ElasticBody;

class CollisionSimulator {
public:
  CollisionSimulator(ElasticBody &bodyA, ElasticBody &bodyB);
  ~CollisionSimulator();

  void detectAndSimulateCollision();
  const Vector2D<double> &avgVelBeforeCollision() const;
  bool collisionOccured() const;
  double separationVelocity() const;

private:
  ElasticBody &bodyA_;
  ElasticBody &bodyB_;
  Vector2D<double> avgVelBeforeCollision_;
  bool collisionDetected_;
  double separationVelocity_;
};
