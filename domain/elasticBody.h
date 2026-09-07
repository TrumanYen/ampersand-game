#pragma once

#include <toolkit/vector2d.h>

class MapState;

class ElasticBody {
public:
  ElasticBody(const MapState &mapState, double collisionCoefficient,
              const Vector2D<double> &spawnPoint,
              const Vector2D<double> &initialVelocity);

  ~ElasticBody();

  void accelerate(const Vector2D<double> &acceleration);
  void incrementTime(double timeSeconds);
  void setVelocity(const Vector2D<double> &velocity);

  const Vector2D<double> &position() const;
  const Vector2D<double> &velocity() const;

private:
  void attemptDisplacement(const Vector2D<double> &displacement);

private:
  const MapState &mapState_;
  const double collisionCoefficient_;

  Vector2D<double> pos_;
  Vector2D<double> vel_;
  Vector2D<double> accel_;
};
