#pragma once

#include <memory>

class AmpersandStatus;
class SimulationDomain;
enum class ThrusterState;

class UseCase {
public:
  UseCase(SimulationDomain &domain);
  ~UseCase();

  const AmpersandStatus &friendlyAmpersandStatus() const;
  const AmpersandStatus &enemyAmpersandStatus() const;
  double mapWidthMeters() const;

  void commandFriendlyThrusterState(ThrusterState state);
  void setNewAspectRatio(double heightToWidthRatio);
  void incrementTime(double timeSeconds);

private:
  SimulationDomain &domain_;
  std::unique_ptr<AmpersandStatus> friendlyAmpersandStatus_;
  std::unique_ptr<AmpersandStatus> enemyAmpersandStatus_;
};
