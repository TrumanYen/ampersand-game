#pragma once

#include <utility>

class MapState {
public:
  MapState();
  ~MapState();

  void incrementTime(double timeSeconds);
  void setNewAspectRatio(double heightToWidthAspectRatio);

  double mapWidthMeters() const;
  double mapHeightMeters() const;
  double floorVelocity() const;
  std::pair<double, double> topLeft() const;
  std::pair<double, double> topRight() const;

private:
  double maxX_;
  double maxY_;
  double floorDisplacementSinceLastFrame_;
  double floorVelocity_;
};
