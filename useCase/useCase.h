#pragma once

#include <domain/vector2d.h>
#include <memory>
#include <vector>

class Ampersand;
class EnemyPilot;
class ParticleManager;
class SimulationDomain;
enum class ThrusterState;

class UseCase {
public:
  UseCase(SimulationDomain &domain);
  ~UseCase();

  const Ampersand &friendlyAmpersand() const;
  const Ampersand &enemyAmpersand() const;
  double mapWidthMeters() const;
  void putTheParticlesInTheBag(std::vector<Vector2D<double>> &theBag) const;

  void commandFriendlyThrusterState(ThrusterState state);
  void setNewAspectRatio(double heightToWidthRatio);
  void incrementTime(double timeSeconds);

private:
  SimulationDomain &domain_;
  std::unique_ptr<Ampersand> friendlyAmpersand_;
  std::unique_ptr<Ampersand> enemyAmpersand_;
  std::unique_ptr<EnemyPilot> enemyPilot_;
  std::unique_ptr<ParticleManager> particles_;
};
