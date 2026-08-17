#pragma once

#include <domain/vector2d.h>

class MapState {
public:
  MapState();
  ~MapState();

  void incrementTime(double timeSeconds);
  void setNewAspectRatio(double heightToWidthAspectRatio);

  double mapWidthMeters() const;
  double mapHeightMeters() const;
  double floorVelocity() const;

  Vector2D<double> topLeft() const;
  Vector2D<double> topRight() const;

private:
  double maxX_;
  double maxY_;
  double floorDisplacementSinceLastFrame_;
  double floorVelocity_;
};
