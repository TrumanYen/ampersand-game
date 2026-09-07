#pragma once

#include <cstdint>
#include <deque>
#include <random>
#include <vector>

#include <domain/vector2d.h>

class ElasticBodyRegistry;

class ShrapnelManager {
public:
  ShrapnelManager(ElasticBodyRegistry &elasticBodyRegistry);

  ~ShrapnelManager();

  void incrementTime(double deltaTimeSeconds);
  void putTheShrapnelInTheBag(std::vector<Vector2D<double>> &theBag) const;
  void createShrapnelPiecesAt(const Vector2D<double> &blastLocation,
                              double collisionVelocity);

private:
  double randomDouble(double min, double max);
  double generateShrapnelVelFromCollisionVel(double collisionVelocity);

private:
  ElasticBodyRegistry &elasticBodyRegistry_;
  double currentTimeSeconds_;
  std::deque<std::pair<uint64_t, double>> idToExpiryTimeQueue_;
  std::minstd_rand rng_;
};
