#include <ampersandGameContainer.h>

#include <adapter/viewModel.h>
#include <domain/simulationDomain.h>
#include <external/ampersandGameTui.h>
#include <useCase/useCase.h>

AmpersandGameContainer::AmpersandGameContainer()
    : simulationDomain_(std::make_unique<SimulationDomain>()),
      useCase_(std::make_unique<UseCase>(*simulationDomain_)),
      viewModel_(std::make_unique<ViewModel>(*useCase_)),
      presenter_(std::make_unique<AmpersandGameTui>(*viewModel_)) {}

AmpersandGameContainer::~AmpersandGameContainer() = default;

AmpersandGameTui &AmpersandGameContainer::presenter() { return *presenter_; }
