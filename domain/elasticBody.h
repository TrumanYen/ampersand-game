#pragma once

#include <domain/vector2d.h>

class MapState;

class ElasticBody {
public:
  ElasticBody(const MapState &mapState, Vector2D<double> spawnPoint);

  ~ElasticBody();

  void accelerate(Vector2D<double> acceleration);
  void incrementTime(double timeSeconds);

  Vector2D<double> position() const;
  Vector2D<double> velocity() const;

private:
  void attemptDisplacement(Vector2D<double> displacement);

private:
  const MapState &mapState_;

  Vector2D<double> pos_;
  Vector2D<double> vel_;
  Vector2D<double> accel_;
};
