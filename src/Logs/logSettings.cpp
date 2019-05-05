#include "logSettings.hpp"

using PopHead::Logs::LogSettings;
using PopHead::Logs::ModuleID;
using PopHead::Logs::LogType;
using PopHead::Logs::Log;

LogSettings::LogSettings()
	:mShouldLogIntoConsole(true)
	,mShouldLogIntoFile(true)
{
	setWritingEachLog();
}

void LogSettings::setWritingLogs(bool enabled)
{
	mShouldLogIntoConsole = enabled;
	mShouldLogIntoFile = enabled;
}

void LogSettings::setWritingEachLog()
{
	setWritingLogsFromEachModules();
	setWritingLogsFromEachLogTypes();
}

void LogSettings::setWritingLogsFromEachModules()
{
	setWritingLogsOnlyFromCertainModules(
		{ ModuleID::Base, ModuleID::Inputs, ModuleID::Logs, ModuleID::Music, ModuleID::Physics,
		ModuleID::Renderer, ModuleID::Resources, ModuleID::Sound, ModuleID::States, ModuleID::None }
	);
}

void LogSettings::setWritingLogsFromEachLogTypes() 
{
	setWritingLogsOnlyFromCertainTypes( { LogType::ERROR, LogType::INFO, LogType::WARNING } );
}

bool LogSettings::shouldThisLogBeWrittenIntoConsole(const Log& log) const
{
	return mShouldLogIntoConsole && shouldThisLogBeWritten(log);
}

bool LogSettings::shouldThisLogBeWrittenIntoFile(const Log& log) const
{
	return mShouldLogIntoFile && shouldThisLogBeWritten(log);
}

bool LogSettings::shouldThisLogBeWritten(const Log& log) const
{
	return shouldThisLogBeWrittenConsideringLogType(log) && shouldThisLogBeWrittenConsideringModuleID(log);
}

bool LogSettings::shouldThisLogBeWrittenConsideringLogType(const Log& log) const
{
	for (auto type : mTypesOfLogToWrite) {
		if (type == log.type) {
			return true;
		}
	}
	return false;
}

bool LogSettings::shouldThisLogBeWrittenConsideringModuleID(const Log& log) const
{
	for (auto moduleID : mLogFromModulesToWrite){
		if (moduleID == log.moduleID){
			return true;
		}
	}
	return false;
}