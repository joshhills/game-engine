#include "Logger.h"

// Initialize defaults.
// TODO: Is it necessary that this goes here?
std::string Logger::prefix = "$";
std::string Logger::separator = ":";
std::string Logger::filter = "";
Logger::LOG_LEVEL Logger::level = DEBUG;
bool Logger::levelExclusive = false;

string Logger::GetFilter()
{
	return filter;
}

void Logger::SetFilter(string filter)
{
	Logger::filter = filter;
}

Logger::LOG_LEVEL Logger::GetLevel()
{
	return level;
}

void Logger::SetLevel(LOG_LEVEL level)
{
	Logger::level = level;
}

bool Logger::GetLevelExclusive()
{
	return levelExclusive;
}

void Logger::SetLevelExclusive(bool levelExclusive)
{
	Logger::levelExclusive = levelExclusive;
}

void Logger::Log(LOG_LEVEL level, string id, string message)
{
	// Perform id filtering check.
	if (filter != "" && id != filter) {
		return;
	}

	// Perform log level checks.
	if (levelExclusive && Logger::level != level) {
		return;
	}
	if (Logger::level > level) {
		return;
	}

	cout << prefix << " "
		 << separator << " "
		 << id << " "
		 << separator << " "
		 << level << " "
		 << separator << " "
		 << message
		 << endl;
}

void Logger::Debug(string id, string message)
{
	Log(DEBUG, id, message);
}

void Logger::Info(string id, string message)
{
	Log(INFO, id, message);
}

void Logger::Warn(string id, string message)
{
	Log(WARN, id, message);
}

void Logger::Error(string id, string message)
{
	Log(FAIL, id, message);
}

