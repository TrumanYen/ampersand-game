#pragma once

#include <domain/vector2d.h>

class AmpersandSimulation;
enum class ThrusterState;

class Ampersand {
public:
  // ideally should take in a interface of the underlying sim but we don't have
  // that yet
  Ampersand(AmpersandSimulation &ampersand);
  ~Ampersand();

  ThrusterState currentThrusterState() const;
  Vector2D<double> currentPosition() const;

  void setThrusterState(ThrusterState thrusterState);
  void fireThruster();

private:
  AmpersandSimulation &ampersand_;
  ThrusterState thrusterState_;
};
