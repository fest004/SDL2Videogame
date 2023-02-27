#include <SDL2/SDL.h>
#include <spdlog/sinks/stdout_color_sinks-inl.h>
#include <spdlog/spdlog.h>

#ifndef LOG_H
#define LOG_H

class Log {
public:
  Log() = default;
  ~Log() = default;

  void Init();
  void Shutdown();
};

#endif
