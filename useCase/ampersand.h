#pragma once

#include <domain/vector2d.h>

class ElasticBody;
enum class ThrusterState;

class Ampersand {
public:
  // ideally should take in a interface of the underlying sim but we don't have
  // that yet
  Ampersand(ElasticBody &elasticBody);
  ~Ampersand();

  ThrusterState currentThrusterState() const;
  Vector2D<double> currentPosition() const;

  void setThrusterState(ThrusterState thrusterState);
  void fireThruster();

private:
  ElasticBody &elasticBody_;
  ThrusterState thrusterState_;
};
