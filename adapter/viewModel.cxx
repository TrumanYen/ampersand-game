#include <adapter/viewModel.h>

#include <adapter/tuiCell.h>
#include <algorithm>
#include <toolkit/vector2d.h>
#include <useCase/ampersand.h>
#include <useCase/thrusterState.h>
#include <useCase/useCase.h>

ViewModel::ViewModel(UseCase &useCase)
    : maxXChars_(0), maxYChars_(0), simToTerminalScaleX_(0.0),
      simToTerminalScaleY_(0.0), useCase_(useCase) {}

ViewModel::~ViewModel() = default;

std::vector<TuiCell> ViewModel::cellsToRender() const {
  std::vector<TuiCell> cells;
  addRenderableCellsForShrapnel(cells);
  addRenderableCellsForAmpersand(useCase_.friendlyAmpersand(), TuiColor::Green,
                                 cells);
  addRenderableCellsForAmpersand(useCase_.enemyAmpersand(), TuiColor::Red,
                                 cells);
  return cells;
}

void ViewModel::updateTerminalDimensions(int numCharsX, int numCharsY) {
  maxXChars_ = numCharsX - 1;
  maxYChars_ = numCharsY - 1;
  double heightToWidthAspectRatio =
      2.0 * static_cast<double>(numCharsY) / static_cast<double>(numCharsX);
  useCase_.setNewAspectRatio(heightToWidthAspectRatio);
  simToTerminalScaleX_ =
      static_cast<double>(numCharsX) / useCase_.mapWidthMeters();
  simToTerminalScaleY_ = 0.5 * simToTerminalScaleX_;
}

void ViewModel::incrementTimeMs(int milliseconds) {
  double timeDeltaSeconds = 1e-3 * static_cast<double>(milliseconds);
  useCase_.incrementTime(timeDeltaSeconds);
}

void ViewModel::setThrusterState(ThrusterState state) {
  useCase_.commandFriendlyThrusterState(state);
}

Vector2D<int> ViewModel::scaleFromMapSpaceToTerminalCoords(
    const Vector2D<double> &locMapSpace) const {
  int posXUnbounded = locMapSpace.x * simToTerminalScaleX_;
  int posYUnbounded = locMapSpace.y * simToTerminalScaleY_;
  int posXBounded = std::clamp(posXUnbounded, 0, maxXChars_);
  int posYBounded = std::clamp(posYUnbounded, 0, maxYChars_);

  return Vector2D<int>(posXBounded, posYBounded);
}

void ViewModel::addRenderableCellsForAmpersand(
    const Ampersand &ampersand, TuiColor color,
    std::vector<TuiCell> &cellsOut) const {
  Vector2D<int> loc =
      scaleFromMapSpaceToTerminalCoords(ampersand.currentPosition());
  cellsOut.emplace_back('&', color, loc);
  ThrusterState thrusterState = ampersand.currentThrusterState();
  TuiColor blue = TuiColor::Blue;
  switch (thrusterState) {
  case ThrusterState::Left:
    cellsOut.emplace_back('<', blue, loc + Vector2D<int>(1, 0));
    cellsOut.emplace_back('<', blue, loc + Vector2D<int>(2, 0));
    break;
  case ThrusterState::Right:
    cellsOut.emplace_back('>', blue, loc + Vector2D<int>(-1, 0));
    cellsOut.emplace_back('>', blue, loc + Vector2D<int>(-2, 0));
    break;
  case ThrusterState::Down:
    cellsOut.emplace_back('v', blue, loc + Vector2D<int>(0, -1));
    cellsOut.emplace_back('v', blue, loc + Vector2D<int>(0, -2));
    break;
  case ThrusterState::Up:
    cellsOut.emplace_back('^', blue, loc + Vector2D<int>(0, 1));
    cellsOut.emplace_back('^', blue, loc + Vector2D<int>(0, 2));
    if (loc.y + 2 > maxYChars_) {
      cellsOut.emplace_back('>', blue, Vector2D<int>(loc.x - 1, maxYChars_));
      cellsOut.emplace_back('<', blue, Vector2D<int>(loc.x + 1, maxYChars_));
    }
    if (loc.y + 1 > maxYChars_) {
      cellsOut.emplace_back('>', blue, Vector2D<int>(loc.x - 2, maxYChars_));
      cellsOut.emplace_back('<', blue, Vector2D<int>(loc.x + 2, maxYChars_));
    }
    break;
  case ThrusterState::Off:
  default:
    break;
  }
}

void ViewModel::addRenderableCellsForShrapnel(
    std::vector<TuiCell> &cellsOut) const {
  std::vector<Vector2D<double>> shrapnelLocations;
  useCase_.putTheShrapnelInTheBag(shrapnelLocations);
  TuiColor white = TuiColor::White;
  for (const Vector2D<double> &shrapnelLoc : shrapnelLocations) {
    cellsOut.emplace_back('.', white,
                          scaleFromMapSpaceToTerminalCoords(shrapnelLoc));
  }
}
