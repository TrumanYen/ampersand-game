#include <gameLogicContainer.h>

#include <simulationDomain.h>
#include <simToTerminalScaler.h>

GameLogicContainer::GameLogicContainer()
    : simulationDomain_(std::make_unique<SimulationDomain>()),
      simScaler_(std::make_unique<SimToTerminalScaler>(*simulationDomain_)) {}

GameLogicContainer::~GameLogicContainer() = default;

SimulationDomain &GameLogicContainer::simulationDomain() { return *simulationDomain_; }

SimToTerminalScaler &GameLogicContainer::simScaler() { return *simScaler_; }
