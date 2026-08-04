#include <ampersandStatus.h>

#include <ampersandSimulation.h>

AmpersandStatus::AmpersandStatus(const AmpersandSimulation &ampersand)
    : ampersand_(ampersand) {}

AmpersandStatus::~AmpersandStatus() = default;

ThrusterState AmpersandStatus::currentThrusterState() const {
  return ampersand_.currentThrusterState();
}

std::pair<double, double> AmpersandStatus::currentPosition() const {
  return ampersand_.currentPos();
}
