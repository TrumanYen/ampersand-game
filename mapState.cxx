#include <mapState.h>

namespace {
const double MAP_HEIGHT_M = 6.0;
const double MAP_WIDTH_M_INITIAL_DEFAULT = 10.7; // roughly 16:9 ratio

} // namespace

MapState::MapState()
    : maxX_(MAP_WIDTH_M_INITIAL_DEFAULT), maxY_(MAP_HEIGHT_M),
      rightWallDisplacementSinceLastFrame_(0.0), rightWallVelocity_(0.0) {}

MapState::~MapState() = default;

void MapState::incrementTime(double timeSeconds) {
  rightWallVelocity_ = rightWallDisplacementSinceLastFrame_ / timeSeconds;
  rightWallDisplacementSinceLastFrame_ = 0.0;
}

void MapState::setNewAspectRatio(double widthToHeightAspectRatio) {
  double updatedMaxX = widthToHeightAspectRatio * MAP_HEIGHT_M;
  // Only the right wall can move, because the map's height is fixed.
  rightWallDisplacementSinceLastFrame_ += (updatedMaxX - maxX_);
  maxX_ = updatedMaxX;
}

double MapState::mapWidthMeters() const { return maxX_; }

double MapState::mapHeightMeters() const { return maxY_; }

double MapState::rightWallVelocity() const { return rightWallVelocity_; }
