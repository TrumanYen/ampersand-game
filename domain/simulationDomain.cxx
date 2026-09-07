#include <domain/simulationDomain.h>

#include <domain/collisionSimulator.h>
#include <domain/elasticBody.h>
#include <domain/elasticBodyRegistry.h>
#include <domain/mapState.h>
#include <memory>

SimulationDomain::SimulationDomain()
    : mapState_(std::make_unique<MapState>()),
      elasticBodyRegistry_(std::make_unique<ElasticBodyRegistry>(*mapState_)),
      collidableBodyA_(std::make_unique<ElasticBody>(
          *mapState_, mapState_->topLeft(), Vector2D<double>(0.0, 0.0))),
      collidableBodyB_(std::make_unique<ElasticBody>(
          *mapState_, mapState_->topRight(), Vector2D<double>(0.0, 0.0))),
      collisionSim_(std::make_unique<CollisionSimulator>(*collidableBodyA_,
                                                         *collidableBodyB_)) {}

SimulationDomain::~SimulationDomain() {}

bool SimulationDomain::bodiesHaveCollided() const {
  return collisionSim_->collisionOccured();
}

void SimulationDomain::incrementTime(double timeDeltaSeconds) {
  mapState_->incrementTime(timeDeltaSeconds);
  elasticBodyRegistry_->incrementTimeForAllBodies(timeDeltaSeconds);
  collidableBodyA_->incrementTime(timeDeltaSeconds);
  collidableBodyB_->incrementTime(timeDeltaSeconds);
  collisionSim_->detectAndSimulateCollision();
}

MapState &SimulationDomain::mapState() { return *mapState_; }

ElasticBodyRegistry &SimulationDomain::elasticBodyRegistry() {
  return *elasticBodyRegistry_;
}

ElasticBody &SimulationDomain::collidableBodyA() { return *collidableBodyA_; }

ElasticBody &SimulationDomain::collidableBodyB() { return *collidableBodyB_; }
