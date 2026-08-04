#include <ampersandGameContainer.h>
#include <external/terminalPresenter.h>

int main() {

  AmpersandGameContainer container;
  container.presenter().run();
  return 0;
}
