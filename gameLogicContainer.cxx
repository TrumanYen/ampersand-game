#include <gameLogicContainer.h>

#include <adapter/viewModel.h>
#include <domain/simulationDomain.h>
#include <useCase/useCase.h>

GameLogicContainer::GameLogicContainer()
    : simulationDomain_(std::make_unique<SimulationDomain>()),
      useCase_(std::make_unique<UseCase>(*simulationDomain_)),
      viewModel_(std::make_unique<ViewModel>(*useCase_)) {}

GameLogicContainer::~GameLogicContainer() = default;

SimulationDomain &GameLogicContainer::simulationDomain() {
  return *simulationDomain_;
}

ViewModel &GameLogicContainer::viewModel() { return *viewModel_; }
