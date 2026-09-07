#pragma once

#include <memory>
#include <unordered_map>

#include <domain/vector2d.h>

class ElasticBody;
class MapState;

class ElasticBodyRegistry {
public:
  ElasticBodyRegistry(const MapState &mapState);
  ~ElasticBodyRegistry();

  uint64_t createElasticBody(const Vector2D<double> &initialLocation,
                             const Vector2D<double> &initialVelocity);
  void removeElasticBody(uint64_t id);

  // optionals and references are for the weak.  Use pointers and check for
  // nullptr like an adult
  ElasticBody const *const getElasticBody(uint64_t id) const;

  void incrementTimeForAllBodies(double timeDeltaSeconds);

private:
  const MapState &mapState_;
  uint64_t nextAvailableId_;
  std::unordered_map<uint64_t, std::shared_ptr<ElasticBody>> map_;
};
