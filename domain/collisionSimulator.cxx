#include <domain/collisionSimulator.h>

#include <domain/elasticBody.h>

namespace {
const double AMPERSAND_RADIUS = 0.01;
const double DOUBLE_AMPERSAND_RADIUS = 2.0 * AMPERSAND_RADIUS;
const double DOUBLE_AMPERSAND_RADIUS_SQRD =
    DOUBLE_AMPERSAND_RADIUS * DOUBLE_AMPERSAND_RADIUS;
} // namespace

CollisionSimulator::CollisionSimulator(ElasticBody &bodyA, ElasticBody &bodyB)
    : bodyA_(bodyA), bodyB_(bodyB), collisionDetected_(false) {}

CollisionSimulator::~CollisionSimulator() = default;

void CollisionSimulator::detectAndSimulateCollision() { detectCollision(); }

bool CollisionSimulator::collisionOccured() const { return collisionDetected_; }

void CollisionSimulator::detectCollision() {
  double distanceSquaredMagnitude =
      bodyA_.position().squaredDistanceFrom(bodyB_.position());
  collisionDetected_ =
      (distanceSquaredMagnitude <= DOUBLE_AMPERSAND_RADIUS_SQRD);
}
