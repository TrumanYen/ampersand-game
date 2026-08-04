#include <gameLogicContainer.h>

#include <viewModel.h>
#include <simulationDomain.h>

GameLogicContainer::GameLogicContainer()
    : simulationDomain_(std::make_unique<SimulationDomain>()),
      viewModel_(std::make_unique<ViewModel>(*simulationDomain_)) {}

GameLogicContainer::~GameLogicContainer() = default;

SimulationDomain &GameLogicContainer::simulationDomain() {
  return *simulationDomain_;
}

ViewModel &GameLogicContainer::viewModel() { return *viewModel_; }
