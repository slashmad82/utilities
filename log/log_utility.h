#ifndef LOGUTILITY_H
#define LOGUTILITY_H
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>

#define Log LogUtility::logSafe

//STANDARD LEVEL LOG 
#define COMPLETE_LOG	1
#define DEBUG_DB_LOG	50
#define DEBUG_LOG		100
#define DEBUG_HIGH_LOG	200
#define ERROR_LOG		500
#define STATUS_LOG		1000

//DONT USE THIS
#define INCREASE_LOG	5000

using namespace std;

class LogUtility
{
public:
	LogUtility() {};
	static unsigned long localLogLevel;			// Log level setted locally (0 use configuredLogLevel log level)
	static unsigned long consoleLogLevel;		// Log level print into console
	static unsigned long configuredLogLevel;	// Log level configured in windows register
	static bool consolePrint;			
	static void init();					// Call this in main before use log function

	static string sStringToStringMonoline(stringstream * stream);			// Remove new line e carridge return
	static string sStringToStringMonoline(string const& str);				// Remove new line e carridge return
	static void logSafe(const unsigned long &logLevel, string const& str);			// Log to file and console
	static void logSafeConsole(const unsigned long &logLevel, string const& str);	// Log to console only
	static void logSafeFile(const unsigned long &logLevel, string const& str);		// Log to file only
	static bool checkLogLevel(const unsigned long &logLevel);						// Check current log level
	static string logLevelToString(const unsigned long &logLevel);					// Convert log level in printable text
	static string localLogLevelString();									// String with current file log level
	static string consoleLogLevelString();									// String with current console log level
	static string generateUID();											// Gemeare unique UID string time based
	//static string now();
};

#endif
