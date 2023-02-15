#include <SDL2/SDL.h>
#include <spdlog/sinks/stdout_color_sinks-inl.h>
#include <spdlog/spdlog.h>

class Log {
public:
  Log() = default;
  ~Log() = default;

  void Init();
  void Shutdown();
};
