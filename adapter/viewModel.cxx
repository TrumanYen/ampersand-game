#include <adapter/viewModel.h>

#include <adapter/tuiCell.h>
#include <algorithm>
#include <domain/thrusterState.h>
#include <useCase/ampersand.h>
#include <useCase/useCase.h>

ViewModel::ViewModel(UseCase &useCase)
    : maxXChars_(0), maxYChars_(0), simToTerminalScaleX_(0.0),
      simToTerminalScaleY_(0.0), useCase_(useCase) {}

ViewModel::~ViewModel() = default;

std::vector<TuiCell> ViewModel::cellsToRender() const {
  std::vector<TuiCell> cells;
  addRenderableCellsForAmpersand(useCase_.friendlyAmpersand(), TuiColor::Green,
                                 cells);
  addRenderableCellsForAmpersand(useCase_.enemyAmpersand(), TuiColor::Red,
                                 cells);
  return cells;
}

bool ViewModel::gameOver() const { return useCase_.gameOver(); }

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

Vector2D<int>
ViewModel::ampersandPositionCharsXY(const Ampersand &ampersand) const {

  Vector2D<double> currentPosMeters = ampersand.currentPosition();

  int posXUnbounded = currentPosMeters.x * simToTerminalScaleX_;
  int posYUnbounded = currentPosMeters.y * simToTerminalScaleY_;
  int posXBounded = std::clamp(posXUnbounded, 0, maxXChars_);
  int posYBounded = std::clamp(posYUnbounded, 0, maxYChars_);

  return Vector2D<int>(posXBounded, posYBounded);
}

void ViewModel::addRenderableCellsForAmpersand(
    const Ampersand &ampersand, TuiColor color,
    std::vector<TuiCell> &cellsOut) const {
  Vector2D<int> loc = ampersandPositionCharsXY(ampersand);
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
