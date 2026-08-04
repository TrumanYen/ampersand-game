#include <adapter/viewModel.h>

#include <algorithm>
#include <useCase/ampersandStatus.h>
#include <useCase/useCase.h>

ViewModel::ViewModel(UseCase &useCase)
    : maxXChars_(0), maxYChars_(0), simToTerminalScaleX_(0.0),
      simToTerminalScaleY_(0.0), useCase_(useCase) {}

ViewModel::~ViewModel() = default;

std::pair<int, int> ViewModel::currentPositionCharsXY() const {
  return ampersandPositionCharsXY(useCase_.friendlyAmpersandStatus());
}

std::pair<int, int> ViewModel::enemyCurrentPositionCharsXY() const {
  return ampersandPositionCharsXY(useCase_.enemyAmpersandStatus());
}

ThrusterState ViewModel::enemyCurrentThrusterState() const {
  return useCase_.enemyAmpersandStatus().currentThrusterState();
}

ThrusterState ViewModel::currentThrusterState() const {
  return useCase_.friendlyAmpersandStatus().currentThrusterState();
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

std::pair<int, int>
ViewModel::ampersandPositionCharsXY(const AmpersandStatus &ampersand) const {

  std::pair<double, double> currentPosMeters = ampersand.currentPosition();

  int posXUnbounded = currentPosMeters.first * simToTerminalScaleX_;
  int posYUnbounded = currentPosMeters.second * simToTerminalScaleY_;
  int posXBounded = std::clamp(posXUnbounded, 0, maxXChars_);
  int posYBounded = std::clamp(posYUnbounded, 0, maxYChars_);

  return std::pair<int, int>(posXBounded, posYBounded);
}
