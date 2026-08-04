#include <domain/mapState.h>

namespace {
const double MAP_WIDTH_M = 10.0;
const double MAP_HEIGHT_M_INITIAL_DEFAULT = 5.6; // roughly 16:9 ratio

} // namespace

MapState::MapState()
    : maxX_(MAP_WIDTH_M), maxY_(MAP_HEIGHT_M_INITIAL_DEFAULT),
      floorDisplacementSinceLastFrame_(0.0), floorVelocity_(0.0) {}

MapState::~MapState() = default;

void MapState::incrementTime(double timeSeconds) {
  floorVelocity_ = floorDisplacementSinceLastFrame_ / timeSeconds;
  floorDisplacementSinceLastFrame_ = 0.0;
}

void MapState::setNewAspectRatio(double heightToWidthAspectRatio) {
  double updatedMaxY = heightToWidthAspectRatio * MAP_WIDTH_M;
  // Only the floor can move, because the map's width is fixed.
  floorDisplacementSinceLastFrame_ += (updatedMaxY - maxY_);
  maxY_ = updatedMaxY;
}

double MapState::mapWidthMeters() const { return maxX_; }

double MapState::mapHeightMeters() const { return maxY_; }

double MapState::floorVelocity() const { return floorVelocity_; }

std::pair<double, double> MapState::topLeft() const {
  return std::pair<double, double>(0.0, 0.0);
}

std::pair<double, double> MapState::topRight() const {
  return std::pair<double, double>(maxX_, 0.0);
}
