#pragma once

#include <memory>

class SimulationDomain;
class ViewModel;

class GameLogicContainer {
public:
  GameLogicContainer();
  ~GameLogicContainer();

  SimulationDomain &simulationDomain();
  ViewModel &viewModel();

private:
  std::unique_ptr<SimulationDomain> simulationDomain_;
  std::unique_ptr<ViewModel> viewModel_;
};
