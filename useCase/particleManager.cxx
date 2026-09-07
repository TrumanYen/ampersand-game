#include <random>
#include <useCase/particleManager.h>

#include <domain/elasticBody.h>
#include <domain/elasticBodyRegistry.h>

namespace {
const int NUM_PARTICLES_PER_BLAST = 5;
const double MIN_VELOCITY_PER_COMPONENT_MPS = -10.0;
const double MAX_VELOCITY_PER_COMPONENT_MPS = 10.0;
const double MIN_LIFETIME_SEC = 0.2;
const double MIN_LIFETIME_INCREMENT_PER_PARTICLE = 0.05;
const double MAX_LIFETIME_INCREMENT_PER_PARTICLE = 0.3;
const double MAX_RANDOM_INVERSE = 1.0 / std::minstd_rand::max();
} // namespace

ParticleManager::ParticleManager(ElasticBodyRegistry &elasticBodyRegistry)
    : elasticBodyRegistry_(elasticBodyRegistry), currentTimeSeconds_(0.0),
      rng_(std::random_device{}()) {}

ParticleManager::~ParticleManager() = default;

void ParticleManager::incrementTime(double deltaTimeSeconds) {
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

void ParticleManager::putTheParticlesInTheBag(
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

void ParticleManager::createParticlesAt(const Vector2D<double> &blastLocation) {
  double earliestExpiryTime = currentTimeSeconds_ + MIN_LIFETIME_SEC;
  if (!idToExpiryTimeQueue_.empty()) {
    // We can't insert particles that will expire earlier than anything already
    // in the queue, as this would break how we check for expired particles
    earliestExpiryTime =
        std::max(earliestExpiryTime, idToExpiryTimeQueue_.back().second);
  }
  for (int i = 0; i < NUM_PARTICLES_PER_BLAST; i++) {
    Vector2D<double> initialVelocity(
        randomDouble(MIN_VELOCITY_PER_COMPONENT_MPS,
                     MAX_VELOCITY_PER_COMPONENT_MPS),
        randomDouble(MIN_VELOCITY_PER_COMPONENT_MPS,
                     MAX_VELOCITY_PER_COMPONENT_MPS));
    uint64_t id =
        elasticBodyRegistry_.createElasticBody(blastLocation, initialVelocity);
    double expiryTimeDeltaFromPreviousParticle =
        randomDouble(MIN_LIFETIME_INCREMENT_PER_PARTICLE,
                     MAX_LIFETIME_INCREMENT_PER_PARTICLE);
    earliestExpiryTime += expiryTimeDeltaFromPreviousParticle;
    idToExpiryTimeQueue_.emplace_back(id, earliestExpiryTime);
  }
}

double ParticleManager::randomDouble(double min, double max) {
  // if (max <= min){ just don't do that bro this is a private function use it
  // responsibly};
  double randomNormalized = rng_() * MAX_RANDOM_INVERSE;
  return min + ((max - min) * randomNormalized);
}
