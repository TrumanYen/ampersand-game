#include <external/terminalPresenter.h>
#include <gameLogicContainer.h>

int main() {

  GameLogicContainer container;
  container.presenter().run();
  return 0;
}
