#include <random>
#include <useCase/shrapnelManager.h>

#include <domain/elasticBody.h>
#include <domain/elasticBodyRegistry.h>

namespace {
const int SHRAPNEL_COUNT_PER_BLAST = 5;

const double SHRAPNEL_VELOCITY_FACTOR = 0.8;

const double MIN_LIFETIME_SEC = 0.2;
const double MIN_LIFETIME_INCREMENT_PER_PARTICLE = 0.05;
const double MAX_LIFETIME_INCREMENT_PER_PARTICLE = 0.3;

const double SHRAPNEL_ELASTICITY = 0.6;

const double MAX_RANDOM_INVERSE = 1.0 / std::minstd_rand::max();
} // namespace

ShrapnelManager::ShrapnelManager(ElasticBodyRegistry &elasticBodyRegistry)
    : elasticBodyRegistry_(elasticBodyRegistry), currentTimeSeconds_(0.0),
      rng_(std::random_device{}()) {}

ShrapnelManager::~ShrapnelManager() = default;

void ShrapnelManager::incrementTime(double deltaTimeSeconds) {
  currentTimeSeconds_ += deltaTimeSeconds;
  while (!idToExpiryTimeQueue_.empty()) {
    std::pair<uint64_t, double> oldestParticle = idToExpiryTimeQueue_.front();
    if (oldestParticle.second > currentTimeSeconds_) {
      break;
    }
    elasticBodyRegistry_.removeElasticBody(oldestParticle.first);
    idToExpiryTimeQueue_.pop_front();
  }
}

void ShrapnelManager::putTheShrapnelInTheBag(
    std::vector<Vector2D<double>> &theBag) const {
  theBag.clear();
  for (const std::pair<uint64_t, double> &idToExpiryPair :
       idToExpiryTimeQueue_) {
    ElasticBody const *const elasticBody =
        elasticBodyRegistry_.getElasticBody(idToExpiryPair.first);
    if (elasticBody != nullptr) {
      theBag.push_back(elasticBody->position());
    }
  }
}

void ShrapnelManager::createShrapnelPiecesAt(
    const Vector2D<double> &blastLocation, double collisionVelocity) {
  double earliestExpiryTime = currentTimeSeconds_ + MIN_LIFETIME_SEC;
  if (!idToExpiryTimeQueue_.empty()) {
    // We can't insert shrapnel that will expire earlier than anything already
    // in the queue, as this would break how we check for expired shrapnel
    earliestExpiryTime =
        std::max(earliestExpiryTime, idToExpiryTimeQueue_.back().second);
  }
  for (int i = 0; i < SHRAPNEL_COUNT_PER_BLAST; i++) {
    Vector2D<double> initialVelocity(
        generateShrapnelVelFromCollisionVel(collisionVelocity),
        generateShrapnelVelFromCollisionVel(collisionVelocity));
    uint64_t id = elasticBodyRegistry_.createElasticBody(
        SHRAPNEL_ELASTICITY, blastLocation, initialVelocity);
    double expiryTimeDeltaFromPreviousParticle =
        randomDouble(MIN_LIFETIME_INCREMENT_PER_PARTICLE,
                     MAX_LIFETIME_INCREMENT_PER_PARTICLE);
    earliestExpiryTime += expiryTimeDeltaFromPreviousParticle;
    idToExpiryTimeQueue_.emplace_back(id, earliestExpiryTime);
  }
}

double ShrapnelManager::randomDouble(double min, double max) {
  // if (max <= min){ just don't do that bro this is a private function use it
  // responsibly};
  double randomNormalized = rng_() * MAX_RANDOM_INVERSE;
  return min + ((max - min) * randomNormalized);
}

double
ShrapnelManager::generateShrapnelVelFromCollisionVel(double collisionVelocity) {
  return randomDouble(-1.0 * SHRAPNEL_VELOCITY_FACTOR * collisionVelocity,
                      SHRAPNEL_VELOCITY_FACTOR * collisionVelocity);
}
