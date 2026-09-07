#include <ampersandGameContainer.h>
#include <chrono>
#include <external/ampersandGameTui.h>
#include <filesystem>
#include <format>
#include <toolkit/logger.h>

std::string getTimestampedLogPath() {
  std::chrono::time_point now = std::chrono::system_clock::now();
  return std::format("{:%Y-%m-%d_%H-%M-%S}", now);
}

int main() {
  std::filesystem::path logDir = std::filesystem::current_path() / ".log";
  std::filesystem::path logPath = logDir / (getTimestampedLogPath() + ".log");
  std::filesystem::create_directories(logDir);
  Logger::getInstance().initLog(logPath);
  AmpersandGameContainer container;
  container.presenter().run();
  return 0;
}
