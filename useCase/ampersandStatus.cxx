#include <useCase/ampersandStatus.h>

#include <domain/ampersandSimulation.h>

AmpersandStatus::AmpersandStatus(const AmpersandSimulation &ampersand)
    : ampersand_(ampersand) {}

AmpersandStatus::~AmpersandStatus() = default;

ThrusterState AmpersandStatus::currentThrusterState() const {
  return ampersand_.currentThrusterState();
}

Vector2D<double> AmpersandStatus::currentPosition() const {
  return ampersand_.currentPos();
}
