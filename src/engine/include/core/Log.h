#ifndef PINE_LOG_H
#define PINE_LOG_H

#include "spdlog/spdlog.h"

namespace Engine
{
    class ENGINE_API Log
    {
    public:
        static Log* getInstance()
        {
            static Log logger;
            return &logger;
        }

        std::shared_ptr<spdlog::logger> getCoreLogger()
        {
            return m_coreLogger;
        }

        std::shared_ptr<spdlog::logger> getClientLogger()
        {
            return m_clientLogger;
        }

    private:
        explicit Log();
        ~Log() = default;
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;

        void init();

    private:
        std::shared_ptr<spdlog::logger> m_coreLogger;
        std::shared_ptr<spdlog::logger> m_clientLogger;
    };

} // namespace Engine

#define PN_LOG_TRACE(...)                                                                                              \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger().get(), spdlog::level::trace, __VA_ARGS__)
#define PN_LOG_DEBUG(...)                                                                                              \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define PN_LOG_INFO(...)                                                                                               \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger().get(), spdlog::level::info, __VA_ARGS__)
#define PN_LOG_WARN(...)                                                                                               \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger().get(), spdlog::level::warn, __VA_ARGS__)
#define PN_LOG_ERROR(...)                                                                                              \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger().get(), spdlog::level::err, __VA_ARGS__)

#define PN_LOG_APP_TRACE(...)                                                                                          \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger().get(), spdlog::level::trace, __VA_ARGS__)
#define PN_LOG_APP_DEBUG(...)                                                                                          \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger().get(), spdlog::level::debug, __VA_ARGS__)
#define PN_LOG_APP_INFO(...)                                                                                           \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger().get(), spdlog::level::info, __VA_ARGS__)
#define PN_LOG_APP_WARN(...)                                                                                           \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger().get(), spdlog::level::warn, __VA_ARGS__)
#define PN_LOG_APP_ERROR(...)                                                                                          \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger().get(), spdlog::level::err, __VA_ARGS__)

#endif // PINE_LOG_H
