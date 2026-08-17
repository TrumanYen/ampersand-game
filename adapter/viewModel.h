#pragma once

#include <ncurses.h>
#include <utility>
#include <vector>

class AmpersandStatus;
class UseCase;
enum class ThrusterState;
struct TuiCell;
enum class TuiColor;

class ViewModel {
public:
  ViewModel(UseCase &useCase);

  ~ViewModel();

  std::vector<TuiCell> cellsToRender() const;
  bool gameOver() const;

  void updateTerminalDimensions(int numCharsX, int numCharsY);
  void incrementTimeMs(int milliseconds);
  void setThrusterState(ThrusterState state);

private:
  std::pair<int, int>
  ampersandPositionCharsXY(const AmpersandStatus &ampersand) const;
  void addRenderableCellsForAmpersand(const AmpersandStatus &ampersand,
                                      TuiColor color,
                                      std::vector<TuiCell> &cellsOut) const;

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;

  UseCase &useCase_;
};
