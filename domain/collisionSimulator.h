#pragma once

class ElasticBody;

class CollisionSimulator {
public:
  CollisionSimulator(ElasticBody& bodyA, ElasticBody& bodyB);
  ~CollisionSimulator();

  void detectAndSimulateCollision();
  bool collisionOccured() const;

private:
  void detectCollision();

private:
  ElasticBody &bodyA_;
  ElasticBody &bodyB_;
  bool collisionDetected_;
};
