#pragma once

#include <memory>

class SimulationDomain;
class AmpersandGameTui;
class UseCase;
class ViewModel;

class AmpersandGameContainer {
public:
  AmpersandGameContainer();
  ~AmpersandGameContainer();

  AmpersandGameTui &presenter();

private:
  std::unique_ptr<SimulationDomain> simulationDomain_;
  std::unique_ptr<UseCase> useCase_;
  std::unique_ptr<ViewModel> viewModel_;
  std::unique_ptr<AmpersandGameTui> presenter_;
};
