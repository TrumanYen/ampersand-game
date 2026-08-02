#include <utility>

class Simulation {
  // All units of distance in meters
public:
  Simulation(double maxX, double maxY);
  ~Simulation();

  void incrementTimeMs(double deltaMs);

  void incrementVelocity(double deltaVelX, double deltaVelY);

  std::pair<double, double> currentPos();

private:
  void incrementPosition(double deltaX, double deltaY);

private:
  double maxX_;
  double maxY_;

  double xPos_;
  double yPos_;
  double xVel_;
  double yVel_;
};
