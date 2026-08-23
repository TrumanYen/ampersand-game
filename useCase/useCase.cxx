#include <useCase/useCase.h>

#include <domain/ampersandSimulation.h>
#include <domain/mapState.h>
#include <domain/simulationDomain.h>
#include <useCase/ampersand.h>
#include <useCase/enemyPilot.h>

UseCase::UseCase(SimulationDomain &domain)
    : domain_(domain), enemyPilot_(std::make_unique<EnemyPilot>(
                           domain.ampersandSim(), domain.enemyAmpersandSim())),
      friendlyAmpersand_(std::make_unique<Ampersand>(domain.ampersandSim())),
      enemyAmpersand_(std::make_unique<Ampersand>(domain.enemyAmpersandSim())) {
}

UseCase::~UseCase() = default;

const Ampersand &UseCase::friendlyAmpersand() const {
  return *friendlyAmpersand_;
}

const Ampersand &UseCase::enemyAmpersand() const { return *enemyAmpersand_; }

double UseCase::mapWidthMeters() const {
  return domain_.mapState().mapWidthMeters();
}

bool UseCase::gameOver() const { return domain_.ampersandsHaveCollided(); }

void UseCase::commandFriendlyThrusterState(ThrusterState state) {
  domain_.ampersandSim().setThrusterState(state);
}

void UseCase::setNewAspectRatio(double heightToWidthRatio) {
  domain_.mapState().setNewAspectRatio(heightToWidthRatio);
}

void UseCase::incrementTime(double timeSeconds) {
  enemyPilot_->update(timeSeconds);
  domain_.incrementTime(timeSeconds);
}
