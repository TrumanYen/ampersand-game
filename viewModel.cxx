#include <algorithm>
#include <ampersandSimulation.h>
#include <mapState.h>
#include <simulationDomain.h>
#include <viewModel.h>

ViewModel::ViewModel(SimulationDomain &simulationDomain)
    : maxXChars_(0), maxYChars_(0), simToTerminalScaleX_(0.0),
      simToTerminalScaleY_(0.0), simulationDomain_(simulationDomain) {}

ViewModel::~ViewModel() = default;

std::pair<int, int> ViewModel::currentPositionCharsXY() const {
  return ampersandPositionCharsXY(simulationDomain_.ampersandSim());
}

std::pair<int, int> ViewModel::enemyCurrentPositionCharsXY() const {
  return ampersandPositionCharsXY(simulationDomain_.enemyAmpersandSim());
}

ThrusterState ViewModel::enemyCurrentThrusterState() const {
  return simulationDomain_.enemyAmpersandSim().currentThrusterState();
}

ThrusterState ViewModel::currentThrusterState() const {
  return simulationDomain_.ampersandSim().currentThrusterState();
}

void ViewModel::updateTerminalDimensions(int numCharsX, int numCharsY) {
  maxXChars_ = numCharsX - 1;
  maxYChars_ = numCharsY - 1;
  double heightToWidthAspectRatio =
      2.0 * static_cast<double>(numCharsY) / static_cast<double>(numCharsX);
  simulationDomain_.mapState().setNewAspectRatio(heightToWidthAspectRatio);
  simToTerminalScaleX_ = static_cast<double>(numCharsX) /
                         simulationDomain_.mapState().mapWidthMeters();
  simToTerminalScaleY_ = 0.5 * simToTerminalScaleX_;
}

void ViewModel::incrementTimeMs(int milliseconds) {
  double timeDeltaSeconds = 1e-3 * static_cast<double>(milliseconds);
  simulationDomain_.incrementTime(timeDeltaSeconds);
}

void ViewModel::setThrusterState(ThrusterState state) {
  simulationDomain_.ampersandSim().setThrusterState(state);
}

std::pair<int, int> ViewModel::ampersandPositionCharsXY(
    const AmpersandSimulation &ampersand) const {

  std::pair<double, double> currentPosMeters = ampersand.currentPos();

  int posXUnbounded = currentPosMeters.first * simToTerminalScaleX_;
  int posYUnbounded = currentPosMeters.second * simToTerminalScaleY_;
  int posXBounded = std::clamp(posXUnbounded, 0, maxXChars_);
  int posYBounded = std::clamp(posYUnbounded, 0, maxYChars_);

  return std::pair<int, int>(posXBounded, posYBounded);
}
