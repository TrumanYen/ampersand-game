#pragma once

class ElasticBody;

class CollisionSimulator {
public:
  CollisionSimulator(ElasticBody &bodyA, ElasticBody &bodyB);
  ~CollisionSimulator();

  void detectAndSimulateCollision();
  bool collisionOccured() const;
  double separationVelocity() const;

private:
  ElasticBody &bodyA_;
  ElasticBody &bodyB_;
  bool collisionDetected_;
  double separationVelocity_;
};
