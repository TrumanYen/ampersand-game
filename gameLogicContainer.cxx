#include <gameLogicContainer.h>

#include <adapter/viewModel.h>
#include <domain/simulationDomain.h>
#include <external/terminalPresenter.h>
#include <useCase/useCase.h>

GameLogicContainer::GameLogicContainer()
    : simulationDomain_(std::make_unique<SimulationDomain>()),
      useCase_(std::make_unique<UseCase>(*simulationDomain_)),
      viewModel_(std::make_unique<ViewModel>(*useCase_)),
      presenter_(std::make_unique<TerminalPresenter>(*viewModel_)) {}

GameLogicContainer::~GameLogicContainer() = default;

TerminalPresenter &GameLogicContainer::presenter() { return *presenter_; }
