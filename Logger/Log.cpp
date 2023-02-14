#include "Log.h"
#include "logger.h"
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>

void Log::Init() {
  auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  consoleSink->set_pattern("%^[%H:%M:%S:%e] %v%$");

  std::vector<spdlog::sink_ptr> sinks{consoleSink};
  auto Logger = std::make_shared<spdlog::logger>(ZELDA_DEFAULT_LOGGER_NAME,
                                                 sinks.begin(), sinks.end());
  Logger->set_level(spdlog::level::trace);
  Logger->flush_on(spdlog::level::trace);
  spdlog::register_logger(Logger);
}

void Log::Shutdown() { spdlog::shutdown(); }
