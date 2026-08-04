#include <external/terminalPresenter.h>
#include <gameLogicContainer.h>

int main() {

  GameLogicContainer container;
  TerminalPresenter presenter(container.viewModel());
  presenter.run();
  return 0;
}
