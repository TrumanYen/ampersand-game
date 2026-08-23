#include <domain/ampersandSimulation.h>

#include <domain/elasticBody.h>
#include <useCase/thrusterState.h>

namespace {
const double THRUSTER_ACCEL_MPSS = 15.0;
} // namespace

AmpersandSimulation::AmpersandSimulation(const MapState &mapState,
                                         Vector2D<double> spawnPoint)
    : physics_(std::make_unique<ElasticBody>(mapState, spawnPoint)),
      thrusterState_(ThrusterState::Off) {}

AmpersandSimulation::~AmpersandSimulation() = default;

void AmpersandSimulation::incrementTime(double timeSeconds) {
  physics_->accelerate(getAccelFromThruster());
  physics_->incrementTime(timeSeconds);
}

void AmpersandSimulation::setThrusterState(ThrusterState state) {
  thrusterState_ = state;
}

Vector2D<double> AmpersandSimulation::currentPos() const {
  return physics_->position();
}

Vector2D<double> AmpersandSimulation::currentVel() const {
  return physics_->velocity();
}

ThrusterState AmpersandSimulation::currentThrusterState() const {
  return thrusterState_;
}

Vector2D<double> AmpersandSimulation::getAccelFromThruster() const {
  Vector2D<double> accel(0.0, 0.0);
  switch (thrusterState_) {
  case ThrusterState::Up:
    accel.y -= THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Down:
    accel.y += THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Left:
    accel.x -= THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Right:
    accel.x += THRUSTER_ACCEL_MPSS;
    break;
  case ThrusterState::Off:
  default:
    break;
  }
  return accel;
}
