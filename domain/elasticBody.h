#pragma once

#include <domain/vector2d.h>

class MapState;

class ElasticBody {
public:
  // TODO: pass in by const ref
  ElasticBody(const MapState &mapState, double collisionCoefficient,
              Vector2D<double> spawnPoint, Vector2D<double> initialVelocity);

  ~ElasticBody();

  void accelerate(Vector2D<double> acceleration);
  void incrementTime(double timeSeconds);
  void setVelocity(Vector2D<double> velocity);

  Vector2D<double> position() const;
  Vector2D<double> velocity() const;

private:
  void attemptDisplacement(Vector2D<double> displacement);

private:
  const MapState &mapState_;
  const double collisionCoefficient_;

  Vector2D<double> pos_;
  Vector2D<double> vel_;
  Vector2D<double> accel_;
};
