#pragma once

#include <memory>

class SimulationDomain;
class TerminalPresenter;
class UseCase;
class ViewModel;

class GameLogicContainer {
public:
  GameLogicContainer();
  ~GameLogicContainer();

  TerminalPresenter &presenter();

private:
  std::unique_ptr<SimulationDomain> simulationDomain_;
  std::unique_ptr<UseCase> useCase_;
  std::unique_ptr<ViewModel> viewModel_;
  std::unique_ptr<TerminalPresenter> presenter_;
};
