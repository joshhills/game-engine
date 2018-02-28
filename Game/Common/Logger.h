#pragma once

#include <string>
#include <iostream>

using namespace std;

class Logger {
public:
	enum LOG_LEVEL {
		DEBUG,
		INFO,
		WARN,
		FAIL
	};

	/* Accessors */

	/**
	 * Get the currently active filter.
	 *
	 * @return A string with an id of a service.
	 */
	static string GetFilter();

	/**
	 * Set the active filter.
	 *
	 * @param filter A string with the id of a service.
	 */
	static void SetFilter(string filter);

	/**
	 * Return the current level filter of the log.
	 */
	static LOG_LEVEL GetLevel();

	/**
	 * Set the log level filtering to show a
	 * different set of messages.
	 *
	 * @param level The log level.
	 */
	static void SetLevel(LOG_LEVEL level);

	/**
	 * Get whether the log will only emit
	 * messages at the specified log level (true),
	 * or also below it (false).
	 *
	 * @return A boolean representing this constraint.
	 */
	static bool GetLevelExclusive();

	/**
	* Set whether the log will only emit
	* messages at the specified log level (true),
	* or also below it (false).
	*
	* @return A boolean representing this constraint.
	*/
	static void SetLevelExclusive(bool levelExclusive);

	/* Logging Functions */

	/**
	* Log a 'debug' message to the console.
	*
	* @param id			The id of the service to filter against.
	* @param message	The message to emit if it passes filtering.
	*/
	static void Debug(string id, string message);

	/**
	* Log an 'info' message to the console.
	*
	* @param id			The id of the service to filter against.
	* @param message	The message to emit if it passes filtering.
	*/
	static void Info(string id, string message);

	/**
	* Log a 'warn' message to the console.
	*
	* @param id			The id of the service to filter against.
	* @param message	The message to emit if it passes filtering.
	*/
	static void Warn(string id, string message);

	/**
	* Log an 'error' message to the console.
	*
	* @param id			The id of the service to filter against.
	* @param message	The message to emit if it passes filtering.
	*/
	static void Error(string id, string message);
private:
	/* Disallow creating an instance of logger
	 * as it is engine-wide.
	 */
	Logger() {}

	/**
	* Log a message to the console.
	*
	* @param level		The log level to filter against.
	* @param id			The id of the service to filter against.
	* @param message	The message to emit if it passes filtering.
	*/
	static void Log(LOG_LEVEL level, string id, string message);

	static string prefix;		// String to prepend to output.
	static string separator;	// The separator to use between output segments.
	static string filter;		// An id constraint to enforce on output (basic).
	static LOG_LEVEL level;		// A secondary constraint to enforce semantically.
	static bool levelExclusive;	// Whether only the specified level should be emitted.
};