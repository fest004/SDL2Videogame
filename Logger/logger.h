
#include <spdlog/spdlog.h>
#define ZELDA_DEFAULT_LOGGER_NAME "ZeldaLogger"

#ifndef ZELDA_CONFIG_RELEASE

#define ZELDA_TRACE(...)                                                       \
  if (spdlog::get(ZELDA_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(ZELDA_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);                \
  }
#else
#define ZELDA_TRACE(...) (void)0
#endif
