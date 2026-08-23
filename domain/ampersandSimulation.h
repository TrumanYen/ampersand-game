#pragma once

#include <domain/vector2d.h>

#include <memory>

enum class ThrusterState;
class MapState;
class ElasticBody;

class AmpersandSimulation {
  // All units of distance in meters and frame of reference is right down
public:
  AmpersandSimulation(const MapState &mapState, Vector2D<double> spawnPoint);
  ~AmpersandSimulation();

  void incrementTime(double timeSeconds);
  void setThrusterState(ThrusterState state);

  Vector2D<double> currentPos() const;
  Vector2D<double> currentVel() const;
  ThrusterState currentThrusterState() const;

private:
  Vector2D<double> getAccelFromThruster() const;

private:
  std::unique_ptr<ElasticBody> physics_;
  ThrusterState thrusterState_;
};
