#include <memory>
#include <utility>

class Simulation;

enum class Direction { Up, Down, Left, Right };

class ScaledSimulation {
public:
  ScaledSimulation(int numCharsX, int numCharsY);

  ~ScaledSimulation();

  void accelerate(Direction direction);
  void incrementTimeMs(int deltaTimeMs);

  std::pair<int, int> currentPositionCharsXY();

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;

  std::unique_ptr<Simulation> sim_;
};
