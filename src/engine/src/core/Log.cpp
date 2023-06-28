#include "Log.h"
#include "pch.h"

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Engine
{
#ifdef _WIN32
    std::string getexepath()
    {
        char result[FILENAME_MAX];
        return std::string(result, GetModuleFileName(NULL, result, FILENAME_MAX));
    }
#else
    std::string getexepath()
    {
        char result[FILENAME_MAX] = {0};
        ssize_t count = readlink("/proc/self/exe", result, FILENAME_MAX);
        return std::string(result, (count > 0) ? count : 0);
    }
#endif

    std::shared_ptr<spdlog::logger> setup_logger(std::string logger_name, std::vector<spdlog::sink_ptr> sinks)
    {
        auto logger = spdlog::get(logger_name);
        if (!logger)
        {
            if (sinks.size() > 0)
            {
                logger = std::make_shared<spdlog::logger>(logger_name, std::begin(sinks), std::end(sinks));
                spdlog::register_logger(logger);
            }
            else
            {
                logger = spdlog::stdout_color_mt(logger_name);
            }
        }
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        return logger;
    }

    Log* Log::getInstance()
    {
        static auto logger = new Log();
        return logger;
    }

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

        m_coreLogger = setup_logger("PINE", logSinks);
        m_clientLogger = setup_logger("APP", logSinks);
    }

    spdlog::logger* Log::getCoreLogger()
    {
        return m_coreLogger.get();
    }

    spdlog::logger* Log::getClientLogger()
    {
        return m_clientLogger.get();
    }

} // namespace Engine
