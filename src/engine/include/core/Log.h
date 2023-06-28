#ifndef PINE_LOG_H
#define PINE_LOG_H

#include "globel.h"
#include <spdlog/spdlog.h>

NAMESPACE_BEGIN(Engine)
class ENGINE_API Log
{
public:
    static Log* getInstance();
    void init();
    spdlog::logger* getCoreLogger();
    spdlog::logger* getClientLogger();

private:
    explicit Log();
    ~Log() = default;
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

private:
    std::shared_ptr<spdlog::logger> m_coreLogger;
    std::shared_ptr<spdlog::logger> m_clientLogger;
};

NAMESPACE_END(Engine)

#define PN_LOG_TRACE(...)                                                                                              \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger(), spdlog::level::trace, __VA_ARGS__)
#define PN_LOG_DEBUG(...)                                                                                              \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger(), spdlog::level::debug, __VA_ARGS__)
#define PN_LOG_INFO(...)                                                                                               \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger(), spdlog::level::info, __VA_ARGS__)
#define PN_LOG_WARN(...)                                                                                               \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger(), spdlog::level::warn, __VA_ARGS__)
#define PN_LOG_ERROR(...)                                                                                              \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getCoreLogger(), spdlog::level::err, __VA_ARGS__)

#define PN_LOG_APP_TRACE(...)                                                                                          \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger(), spdlog::level::trace, __VA_ARGS__)
#define PN_LOG_APP_DEBUG(...)                                                                                          \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger(), spdlog::level::debug, __VA_ARGS__)
#define PN_LOG_APP_INFO(...)                                                                                           \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger(), spdlog::level::info, __VA_ARGS__)
#define PN_LOG_APP_WARN(...)                                                                                           \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger(), spdlog::level::warn, __VA_ARGS__)
#define PN_LOG_APP_ERROR(...)                                                                                          \
    SPDLOG_LOGGER_CALL(Engine::Log::getInstance()->getClientLogger(), spdlog::level::err, __VA_ARGS__)

#endif // PINE_LOG_H
