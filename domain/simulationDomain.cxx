#include <domain/simulationDomain.h>

#include <domain/collisionSimulator.h>
#include <domain/elasticBody.h>
#include <domain/mapState.h>
#include <memory>

SimulationDomain::SimulationDomain()
    : mapState_(std::make_unique<MapState>()),
      collidableBodyA_(
          std::make_unique<ElasticBody>(*mapState_, mapState_->topLeft())),
      collidableBodyB_(
          std::make_unique<ElasticBody>(*mapState_, mapState_->topRight())),
      collisionSim_(std::make_unique<CollisionSimulator>(*collidableBodyA_,
                                                         *collidableBodyB_)) {}

SimulationDomain::~SimulationDomain() {}

bool SimulationDomain::bodiesHaveCollided() const {
  return collisionSim_->collisionOccured();
}

void SimulationDomain::incrementTime(double timeDeltaSeconds) {
  mapState_->incrementTime(timeDeltaSeconds);
  collidableBodyA_->incrementTime(timeDeltaSeconds);
  collidableBodyB_->incrementTime(timeDeltaSeconds);
  collisionSim_->detectAndSimulateCollision();
}

MapState &SimulationDomain::mapState() { return *mapState_; }

ElasticBody &SimulationDomain::collidableBodyA() { return *collidableBodyA_; }

ElasticBody &SimulationDomain::collidableBodyB() { return *collidableBodyB_; }
