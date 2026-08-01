#include <utility>

class Simulation {
public:
  Simulation(int maxX, int maxY);
  ~Simulation();

  void teleport(int deltaX, int deltaY);
  std::pair<int, int> currentPos();

private:
  int maxX_;
  int maxY_;
  int xPos_;
  int yPos_;
};
