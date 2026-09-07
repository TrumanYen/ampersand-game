#pragma once

#include <filesystem>
#include <fstream>
#include <string_view>

class Logger {
public:
  Logger(const Logger &) = delete;
  void operator=(const Logger &) = delete;

  static Logger &getInstance();

  void initLog(const std::filesystem::path &path);
  void log(std::string_view msg);

private:
  Logger();
  ~Logger();

private:
  std::ofstream fileStream_;
};
