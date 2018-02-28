#include "LoggerInstance.h"

LoggerInstance::LoggerInstance(string id) : id(id)
{}

LoggerInstance::~LoggerInstance()
{}

void LoggerInstance::Debug(string message)
{
	Logger::Debug(id, message);
}

void LoggerInstance::Info(string message)
{
	Logger::Info(id, message);
}

void LoggerInstance::Warn(string message)
{
	Logger::Warn(id, message);
}

void LoggerInstance::Error(string message)
{
	Logger::Error(id, message);
}
