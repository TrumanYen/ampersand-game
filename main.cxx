#include <ampersandGameContainer.h>
#include <external/ampersandGameTui.h>

int main() {

  AmpersandGameContainer container;
  container.presenter().run();
  return 0;
}
