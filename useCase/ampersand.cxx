#include <useCase/ampersand.h>

#include <domain/elasticBody.h>
#include <useCase/thrusterState.h>

namespace {
const double THRUSTER_ACCEL_MPSS = 15.0;
} // namespace

Ampersand::Ampersand(ElasticBody &elasticBody)
    : elasticBody_(elasticBody), thrusterState_(ThrusterState::Off) {}

Ampersand::~Ampersand() = default;

ThrusterState Ampersand::currentThrusterState() const { return thrusterState_; }

Vector2D<double> Ampersand::currentPosition() const {
  return elasticBody_.position();
}

void Ampersand::setThrusterState(ThrusterState thrusterState) {
  thrusterState_ = thrusterState;
}

void Ampersand::fireThruster() {
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
  elasticBody_.accelerate(accel);
}
