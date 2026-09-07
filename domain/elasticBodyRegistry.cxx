#include <domain/elasticBody.h>
#include <domain/elasticBodyRegistry.h>

ElasticBodyRegistry::ElasticBodyRegistry(const MapState &mapState)
    : mapState_(mapState), nextAvailableId_(0) {}

ElasticBodyRegistry::~ElasticBodyRegistry() = default;

uint64_t ElasticBodyRegistry::createElasticBody(
    double collisionCoefficient, const Vector2D<double> &initialLocation,
    const Vector2D<double> &initialVelocity) {
  uint64_t id = nextAvailableId_++;
  map_.insert(
      {id, std::make_shared<ElasticBody>(mapState_, collisionCoefficient,
                                         initialLocation, initialVelocity)});

  return id;
}

void ElasticBodyRegistry::removeElasticBody(uint64_t id) { map_.erase(id); }

ElasticBody const *const
ElasticBodyRegistry::getElasticBody(uint64_t id) const {
  if (map_.contains(id)) {
    return map_.at(id).get();
  }
  return nullptr;
}

void ElasticBodyRegistry::incrementTimeForAllBodies(double timeDeltaSeconds) {
  for (const auto &[id, bodyPtr] : map_) {
    bodyPtr->incrementTime(timeDeltaSeconds);
  }
}
