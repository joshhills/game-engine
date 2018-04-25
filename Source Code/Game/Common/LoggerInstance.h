#pragma once

#include <string>
#include "Logger.h"

using namespace std;

class LoggerInstance {
public:
	LoggerInstance(string id);
	~LoggerInstance();

	/**
	* Log a 'debug' message to the console.
	*
	* @param message	The message to emit if it passes filtering.
	*/
	void Debug(string message);

	/**
	* Log an 'info' message to the console.
	*
	* @param message	The message to emit if it passes filtering.
	*/
	void Info(string message);

	/**
	* Log a 'warn' message to the console.
	*
	* @param message	The message to emit if it passes filtering.
	*/
	void Warn(string message);

	/**
	* Log an 'error' message to the console.
	*
	* @param message	The message to emit if it passes filtering.
	*/
	void Error(string message);
private:
	string id;
};