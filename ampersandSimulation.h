#pragma once

#include <utility>

enum class ThrusterState { Up, Down, Left, Right, Off };

class MapState;

class AmpersandSimulation {
  // All units of distance in meters and frame of reference is right down
public:
  AmpersandSimulation(const MapState &mapState);
  ~AmpersandSimulation();

  void incrementTime(double timeSeconds);
  void setThrusterState(ThrusterState state);

  std::pair<double, double> currentPos() const;
  std::pair<double, double> currentVel() const;
  std::pair<double, double> currentAccel() const;
  ThrusterState currentThrusterState() const;

private:
  void displaceAmpersand(double deltaX, double deltaY);
  void calculateCurrentAcceleration();

private:
  const MapState &mapState_;

  double xPos_;
  double yPos_;
  double xVel_;
  double yVel_;
  double xAccel_;
  double yAccel_;

  ThrusterState thrusterState_;
};
