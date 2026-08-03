#pragma once

class MapState {
public:
  MapState();
  ~MapState();

  void incrementTime(double timeSeconds);
  void setNewAspectRatio(double widthToHeightAspectRatio);

  double mapWidthMeters() const;
  double mapHeightMeters() const;
  double rightWallVelocity() const;

private:
  double maxX_;
  double maxY_;
  double rightWallDisplacementSinceLastFrame_;
  double rightWallVelocity_;
};
