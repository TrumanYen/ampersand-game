#include <utility>

class Simulation {
public:
  Simulation(int maxX, int maxY);
  ~Simulation();

  void incrementPosition(int deltaX, int deltaY); // should make private soon

  std::pair<int, int> currentPos();

private:
  int maxX_;
  int maxY_;
  int xPos_;
  int yPos_;
};
