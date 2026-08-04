#include <useCase/useCase.h>

#include <domain/ampersandSimulation.h>
#include <domain/mapState.h>
#include <domain/simulationDomain.h>
#include <useCase/ampersandStatus.h>
#include <useCase/enemyPilot.h>

UseCase::UseCase(SimulationDomain &domain)
    : domain_(domain), enemyPilot_(std::make_unique<EnemyPilot>(
                           domain.ampersandSim(), domain.enemyAmpersandSim())),
      friendlyAmpersandStatus_(
          std::make_unique<AmpersandStatus>(domain.ampersandSim())),
      enemyAmpersandStatus_(
          std::make_unique<AmpersandStatus>(domain.enemyAmpersandSim())) {}

UseCase::~UseCase() = default;

const AmpersandStatus &UseCase::friendlyAmpersandStatus() const {
  return *friendlyAmpersandStatus_;
}

const AmpersandStatus &UseCase::enemyAmpersandStatus() const {
  return *enemyAmpersandStatus_;
}

double UseCase::mapWidthMeters() const {
  return domain_.mapState().mapWidthMeters();
}

void UseCase::commandFriendlyThrusterState(ThrusterState state) {
  domain_.ampersandSim().setThrusterState(state);
}

void UseCase::setNewAspectRatio(double heightToWidthRatio) {
  domain_.mapState().setNewAspectRatio(heightToWidthRatio);
}

void UseCase::incrementTime(double timeSeconds) {
  enemyPilot_->update();
  domain_.incrementTime(timeSeconds);
}
