#include <gameLogicContainer.h>
#include <terminalPresenter.h>

int main() {

  GameLogicContainer container;
  TerminalPresenter presenter(container.viewModel());
  presenter.run();
  return 0;
}
