
#include <spdlog/spdlog.h>
#define ZELDA_DEFAULT_LOGGER_NAME "ZeldaLogger"

#ifndef ZELDA_CONFIG_RELEASE

#define ZeldaTrace(...)                                                        \
  if (spdlog::get(ZELDA_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(ZELDA_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);                \
  }
#define ZeldaDebug(...)                                                        \
  if (spdlog::get(ZELDA_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(ZELDA_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);                \
  }
#define ZeldaInfo(...)                                                         \
  if (spdlog::get(ZELDA_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(ZELDA_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);                 \
  }
#define ZeldaWarn(...)                                                         \
  if (spdlog::get(ZELDA_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(ZELDA_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);                 \
  }
#define ZeldaError(...)                                                        \
  if (spdlog::get(ZELDA_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(ZELDA_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);                \
  }
#define ZeldaCritical(...)                                                     \
  if (spdlog::get(ZELDA_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(ZELDA_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);             \
  }
#else
// Disable logging for release builds
#define ZeldaTrace(...) (void)0
#define ZeldaDebug(...) (void)0
#define ZeldaInfo(...) (void)0
#define ZeldaWarn(...) (void)0
#define ZeldaError(...) (void)0
#define ZeldaCritical(...) (void)0
#endif
