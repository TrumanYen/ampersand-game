#pragma once

#include <domain/vector2d.h>
#include <ncurses.h>
#include <vector>

class Ampersand;
class UseCase;
enum class ThrusterState;
struct TuiCell;
enum class TuiColor;

class ViewModel {
public:
  ViewModel(UseCase &useCase);

  ~ViewModel();

  std::vector<TuiCell> cellsToRender() const;
  TuiColor backgroundColor() const;

  void updateTerminalDimensions(int numCharsX, int numCharsY);
  void incrementTimeMs(int milliseconds);
  void setThrusterState(ThrusterState state);

private:
  Vector2D<int> ampersandPositionCharsXY(const Ampersand &ampersand) const;
  void addRenderableCellsForAmpersand(const Ampersand &ampersand,
                                      TuiColor color,
                                      std::vector<TuiCell> &cellsOut) const;

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;

  UseCase &useCase_;
};
