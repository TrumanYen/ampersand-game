#include <utility>

class Simulation {
public:
  Simulation(double maxX, double maxY);
  ~Simulation();

  void incrementTimeMs(double deltaMs);

  void incrementVelocity(double deltaVelX,
                         double deltaVelY); // currently chars per millisecond
  void incrementPosition(double deltaX,
                         double deltaY); // should make private soon

  std::pair<double, double> currentPos();

private:
  double maxX_;
  double maxY_;

  double xPos_;
  double yPos_;
  double xVel_;
  double yVel_;
};
