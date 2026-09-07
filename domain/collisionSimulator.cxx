#include <domain/collisionSimulator.h>

#include <domain/elasticBody.h>
#include <limits>

namespace {
const double AMPERSAND_RADIUS = 0.1;
const double DOUBLE_AMPERSAND_RADIUS = 2.0 * AMPERSAND_RADIUS;
const double DOUBLE_AMPERSAND_RADIUS_SQRD =
    DOUBLE_AMPERSAND_RADIUS * DOUBLE_AMPERSAND_RADIUS;
const double COLLISION_EXPLOSION_MULTIPLIER = 3.0;
} // namespace

CollisionSimulator::CollisionSimulator(ElasticBody &bodyA, ElasticBody &bodyB)
    : bodyA_(bodyA), bodyB_(bodyB), collisionDetected_(false) {}

CollisionSimulator::~CollisionSimulator() = default;

void CollisionSimulator::detectAndSimulateCollision() {
  double distanceSquaredMagnitude =
      bodyA_.position().squaredDistanceFrom(bodyB_.position());
  bool bodiesAreOverlapping =
      (distanceSquaredMagnitude < DOUBLE_AMPERSAND_RADIUS_SQRD);
  if (!bodiesAreOverlapping) {
    collisionDetected_ = false;
    return;
  }
  Vector2D<double> normal = bodyB_.position() - bodyA_.position();
  double normalMag = normal.magnitude();
  if (normalMag < std::numeric_limits<double>::epsilon()) {
    // let's try not to divide by zero
    return;
  }
  Vector2D<double> normalNormalized = normal / normalMag;
  Vector2D<double> tangentialNormalized = normalNormalized.normalVector();
  Vector2D<double> relVel = bodyB_.velocity() - bodyA_.velocity();
  separationVelocity_ = relVel.dot(normalNormalized);
  collisionDetected_ = (separationVelocity_ < 0.0);
  if (separationVelocity_ > -0.5) {
    // We should not simulate slow collisions because the bodies will simply
    // stick together
    return;
  }
  double velANormalComp = bodyA_.velocity().dot(normalNormalized);
  double velATangentialComp = bodyA_.velocity().dot(tangentialNormalized);
  double velBNormalComp = bodyB_.velocity().dot(normalNormalized);
  double velBTangentialComp = bodyB_.velocity().dot(tangentialNormalized);

  // Assuming equal masses here, so we simply swap the normal components.  We
  // need to multiply the velocities to make sure they don't stick. Not an ideal
  // solution.
  bodyA_.setVelocity(
      (normalNormalized * velBNormalComp * COLLISION_EXPLOSION_MULTIPLIER) +
      (tangentialNormalized * velATangentialComp));
  bodyB_.setVelocity(
      (normalNormalized * velANormalComp * COLLISION_EXPLOSION_MULTIPLIER) +
      (tangentialNormalized * velBTangentialComp));
}

bool CollisionSimulator::collisionOccured() const { return collisionDetected_; }

double CollisionSimulator::separationVelocity() const {
  return separationVelocity_;
}
