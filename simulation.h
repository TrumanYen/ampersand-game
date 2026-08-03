#pragma once

#include <utility>

enum class ThrusterState { Up, Down, Left, Right, Off };

class Simulation {
  // All units of distance in meters and frame of reference is right down
public:
  Simulation(double widthToHeightAspectRatio);
  ~Simulation();
  // TODO: rearrange order of pubic functions
  std::pair<double, double> mapDimensionsWidthHeight();
  void incrementTimeMs(double deltaMs);

  void setThrusterState(ThrusterState state);
  void setNewAspectRatio(double widthToHeightAspectRatio);

  std::pair<double, double> currentPos();
  std::pair<double, double> currentVel();
  std::pair<double, double> currentAccel();
  ThrusterState currentThrusterState();

private:
  void displaceAmpersand(double deltaX, double deltaY,
                         double rightWallVelocity);
  void calculateCurrentAcceleration();

private:
  double maxX_;
  double maxY_;

  double xPos_;
  double yPos_;
  double xVel_;
  double yVel_;
  double xAccel_;
  double yAccel_;

  ThrusterState thrusterState_;
  double rightWallDisplacementSinceLastFrame_;
};
