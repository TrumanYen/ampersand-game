#pragma once

#include <cstdint>
#include <deque>
#include <random>
#include <vector>

#include <domain/vector2d.h>

class ElasticBodyRegistry;

class ParticleManager {
public:
  ParticleManager(ElasticBodyRegistry &elasticBodyRegistry);

  ~ParticleManager();

  void incrementTime(double deltaTimeSeconds);
  void putTheParticlesInTheBag(std::vector<Vector2D<double>> &theBag) const;
  void createParticlesAt(const Vector2D<double> &blastLocation);

private:
  double randomDouble(double min, double max);

private:
  ElasticBodyRegistry &elasticBodyRegistry_;
  double currentTimeSeconds_;
  std::deque<std::pair<uint64_t, double>> idToExpiryTimeQueue_;
  std::minstd_rand rng_;
};
