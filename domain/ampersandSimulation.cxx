#include <domain/ampersandSimulation.h>

#include <domain/elasticBody.h>
#include <useCase/thrusterState.h>

namespace {
const double THRUSTER_ACCEL_MPSS = 15.0;
} // namespace

AmpersandSimulation::AmpersandSimulation(const MapState &mapState,
                                         Vector2D<double> spawnPoint)
    : physics_(std::make_unique<ElasticBody>(mapState, spawnPoint)) {}

AmpersandSimulation::~AmpersandSimulation() = default;

void AmpersandSimulation::incrementTime(double timeSeconds) {
  physics_->incrementTime(timeSeconds);
}

void AmpersandSimulation::accelerate(Vector2D<double> acceleration) {
  physics_->accelerate(acceleration);
}

Vector2D<double> AmpersandSimulation::currentPos() const {
  return physics_->position();
}

Vector2D<double> AmpersandSimulation::currentVel() const {
  return physics_->velocity();
}
