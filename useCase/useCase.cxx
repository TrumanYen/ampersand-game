#include <useCase/useCase.h>

#include <domain/mapState.h>
#include <domain/simulationDomain.h>
#include <useCase/ampersand.h>
#include <useCase/enemyPilot.h>

UseCase::UseCase(SimulationDomain &domain)
    : domain_(domain),
      friendlyAmpersand_(std::make_unique<Ampersand>(domain.collidableBodyA())),
      enemyAmpersand_(std::make_unique<Ampersand>(domain.collidableBodyB())),
      enemyPilot_(std::make_unique<EnemyPilot>(
          *friendlyAmpersand_, *enemyAmpersand_, domain_.mapState())) {}
UseCase::~UseCase() = default;

const Ampersand &UseCase::friendlyAmpersand() const {
  return *friendlyAmpersand_;
}

const Ampersand &UseCase::enemyAmpersand() const { return *enemyAmpersand_; }

double UseCase::mapWidthMeters() const {
  return domain_.mapState().mapWidthMeters();
}

bool UseCase::damageSustained() const { return domain_.bodiesHaveCollided(); }

void UseCase::commandFriendlyThrusterState(ThrusterState state) {
  friendlyAmpersand_->setThrusterState(state);
}

void UseCase::setNewAspectRatio(double heightToWidthRatio) {
  domain_.mapState().setNewAspectRatio(heightToWidthRatio);
}

void UseCase::incrementTime(double timeSeconds) {
  enemyPilot_->update(timeSeconds);
  friendlyAmpersand_->fireThruster();
  enemyAmpersand_->fireThruster();
  domain_.incrementTime(timeSeconds);
}
