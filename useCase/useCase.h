#pragma once

#include <memory>

class Ampersand;
class EnemyPilot;
class SimulationDomain;
enum class ThrusterState;

class UseCase {
public:
  UseCase(SimulationDomain &domain);
  ~UseCase();

  const Ampersand &friendlyAmpersand() const;
  const Ampersand &enemyAmpersand() const;
  double mapWidthMeters() const;
  bool damageSustained() const;

  void commandFriendlyThrusterState(ThrusterState state);
  void setNewAspectRatio(double heightToWidthRatio);
  void incrementTime(double timeSeconds);

private:
  SimulationDomain &domain_;
  std::unique_ptr<Ampersand> friendlyAmpersand_;
  std::unique_ptr<Ampersand> enemyAmpersand_;
  std::unique_ptr<EnemyPilot> enemyPilot_;
};
