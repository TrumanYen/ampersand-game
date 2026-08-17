#pragma once

#include <domain/vector2d.h>

enum class ThrusterState;
class MapState;

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
  void displaceAmpersand(Vector2D<double> displacement);
  Vector2D<double> currentAcceleration() const;

private:
  const MapState &mapState_;

  Vector2D<double> pos_;
  Vector2D<double> vel_;

  ThrusterState thrusterState_;
};
