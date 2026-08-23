#include <domain/simulationDomain.h>

#include <domain/elasticBody.h>
#include <domain/mapState.h>
#include <memory>

namespace {
const double AMPERSAND_RADIUS = 0.01;
const double DOUBLE_AMPERSAND_RADIUS = 2.0 * AMPERSAND_RADIUS;
const double DOUBLE_AMPERSAND_RADIUS_SQRD =
    DOUBLE_AMPERSAND_RADIUS * DOUBLE_AMPERSAND_RADIUS;
} // namespace

SimulationDomain::SimulationDomain()
    : mapState_(std::make_unique<MapState>()),
      collidableBodyA_(
          std::make_unique<ElasticBody>(*mapState_, mapState_->topLeft())),
      collidableBodyB_(
          std::make_unique<ElasticBody>(*mapState_, mapState_->topRight())) {}

SimulationDomain::~SimulationDomain() {}

bool SimulationDomain::bodiesHaveCollided() const {
  double distanceSquaredMagnitude =
      collidableBodyA_->position().squaredDistanceFrom(
          collidableBodyB_->position());
  if (distanceSquaredMagnitude <= DOUBLE_AMPERSAND_RADIUS_SQRD) {
    return true;
  }
  return false;
}

void SimulationDomain::incrementTime(double timeDeltaSeconds) {
  mapState_->incrementTime(timeDeltaSeconds);
  collidableBodyA_->incrementTime(timeDeltaSeconds);
  collidableBodyB_->incrementTime(timeDeltaSeconds);
}

MapState &SimulationDomain::mapState() { return *mapState_; }

ElasticBody &SimulationDomain::collidableBodyA() { return *collidableBodyA_; }

ElasticBody &SimulationDomain::collidableBodyB() { return *collidableBodyB_; }
