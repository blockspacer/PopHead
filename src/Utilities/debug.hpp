#pragma once

#include "Logs/logger.hpp"
#include "Logs/logRecord.hpp"

#include <stdexcept>

#ifdef PH_DISTRIBUTION
#define PH_BREAKPOINT() ((void)0)

#define PH_LOG(logType, message) ((void)0)

#define PH_ASSERT(expression, message) ((void)0)

#define PH_EXCEPTION(message) throw std::runtime_error(message)

#define PH_ASSERT_EXCEPTION(expression, message) ((void)0)
#else
#ifdef _MSC_VER
#define PH_BREAKPOINT() __debugbreak()
#else
#define PH_BREAKPOINT() ((void)0)
#endif // !_MSC_VER

#define PH_LOG(logType, message)\
	ph::Logger::createLog(logType, message, __FILE__, static_cast<unsigned short>(__LINE__))

#define PH_ASSERT(expression, message) (void)((expression) || (PH_LOG(ph::LogType::Error, message), PH_BREAKPOINT(), 0))

#define PH_EXCEPTION(message) (void)(PH_LOG(ph::LogType::Exception, message), PH_BREAKPOINT(), throw std::runtime_error(message), 0)

#define PH_ASSERT_EXCEPTION(expression, message) (void)((expression) || (PH_EXCEPTION(message), 0))

#endif // !PH_DISTRIBUTION
