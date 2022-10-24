#include "Log.h"
#include "pch.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine
{
#ifdef _WIN32
#include <windows.h>
    std::string getexepath()
    {
        char result[FILENAME_MAX];
        return std::string(result, GetModuleFileName(NULL, result, FILENAME_MAX));
    }
#else
#include <unistd.h>
    std::string getexepath()
    {
        char result[FILENAME_MAX] = {0};
        ssize_t count = readlink("/proc/self/exe", result, FILENAME_MAX);
        return std::string(result, (count > 0) ? count : 0);
    }
#endif

    Log::Log()
    {
        init();
    }

    void Log::init()
    {
        auto currentPath = std::filesystem::path(getexepath()).parent_path();
        currentPath += "/logs/Pine.log";
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(currentPath.string(), true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        m_coreLogger = std::make_shared<spdlog::logger>("PINE", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_coreLogger);
        m_coreLogger->set_level(spdlog::level::trace);
        m_coreLogger->flush_on(spdlog::level::trace);

        m_clientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_clientLogger);
        m_clientLogger->set_level(spdlog::level::trace);
        m_clientLogger->flush_on(spdlog::level::trace);
    }

} // namespace Engine
