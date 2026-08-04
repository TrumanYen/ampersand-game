#pragma once

#include <utility>

class AmpersandStatus;
class UseCase;
enum class ThrusterState;

class ViewModel {
public:
  ViewModel(UseCase &useCase);

  ~ViewModel();

  std::pair<int, int> currentPositionCharsXY() const;
  std::pair<int, int> enemyCurrentPositionCharsXY() const;
  ThrusterState enemyCurrentThrusterState() const;
  ThrusterState currentThrusterState() const;

  void updateTerminalDimensions(int numCharsX, int numCharsY);
  void incrementTimeMs(int milliseconds);
  void setThrusterState(ThrusterState state);

private:
  std::pair<int, int>
  ampersandPositionCharsXY(const AmpersandStatus &ampersand) const;

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;
  UseCase &useCase_;
};
