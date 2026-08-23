#include <useCase/ampersand.h>

#include <domain/ampersandSimulation.h>

Ampersand::Ampersand(const AmpersandSimulation &ampersand)
    : ampersand_(ampersand) {}

Ampersand::~Ampersand() = default;

ThrusterState Ampersand::currentThrusterState() const {
  return ampersand_.currentThrusterState();
}

Vector2D<double> Ampersand::currentPosition() const {
  return ampersand_.currentPos();
}
