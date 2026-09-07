#include <toolkit/logger.h>

Logger::Logger() {}

Logger::~Logger() {}

Logger &Logger::getInstance() {
  static Logger instance;
  return instance;
}

void Logger::initLog(const std::filesystem::path &path) {
  fileStream_.open(path, std::ios::app);
}

void Logger::log(std::string_view msg) {
  if (fileStream_.is_open()) {
    fileStream_ << msg << "\n";
  }
}
