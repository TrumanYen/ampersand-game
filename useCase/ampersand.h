#pragma once

#include <domain/vector2d.h>

class AmpersandSimulation;
enum class ThrusterState;

class Ampersand {
public:
  // ideally should take in a read-only interface but we don't have that yet
  Ampersand(const AmpersandSimulation &ampersand);
  ~Ampersand();

  ThrusterState currentThrusterState() const;
  Vector2D<double> currentPosition() const;

private:
  const AmpersandSimulation &ampersand_;
};
