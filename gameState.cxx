#include <gameState.h>

#include <ampersandSimulation.h>
#include <mapState.h>

GameState::GameState()
    : mapState_(std::make_unique<MapState>()),
      ampersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topLeft())),
      enemyAmpersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topRight())) {}

GameState::~GameState() {}

void GameState::incrementTimeMs(double timeDeltaMs) {
  double timeDeltaSeconds = 1e-3 * timeDeltaMs;
  mapState_->incrementTime(timeDeltaSeconds);
  ampersandSim_->incrementTime(timeDeltaSeconds);
  enemyAmpersandSim_->incrementTime(timeDeltaSeconds);
}

MapState &GameState::mapState() { return *mapState_; }

AmpersandSimulation &GameState::ampersandSim() { return *ampersandSim_; }

AmpersandSimulation &GameState::enemyAmpersandSim() {
  return *enemyAmpersandSim_;
}
