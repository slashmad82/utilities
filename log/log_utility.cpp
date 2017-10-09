#include "log_utility.h"

unsigned long LogUtility::localLogLevel = 0;
unsigned long LogUtility::consoleLogLevel = 0;
unsigned long LogUtility::configuredLogLevel = 0;
bool LogUtility::consolePrint = false;
void LogUtility::init()
{
	localLogLevel = 0;
	consoleLogLevel = DEBUG_LOG;
	configuredLogLevel = 0;
}

string LogUtility::sStringToStringMonoline(stringstream * stream)
{
	string st;
	st = stream->str();
	while(st.find("\r") != string::npos)
		st.replace(st.find("\r"), 1, " ");
	while(st.find("\n") != string::npos)
		st.replace(st.find("\n"), 1, " ");
	return st+"\0";
}

string LogUtility::sStringToStringMonoline(string const& str)
{
	string st = str;
	while(st.find("\r") != string::npos)
		st.replace(st.find("\r"), 1, " ");
	while(st.find("\n") != string::npos)
		st.replace(st.find("\n"), 1, " ");
	return st+"\0";
}

void LogUtility::logSafe(const unsigned long &logLevel, string const& str)
{
	logSafeConsole(logLevel, str);
	logSafeFile(logLevel, str);
}

void LogUtility::logSafeConsole(const unsigned long &logLevel, string const& str)
{
	if (consoleLogLevel > 0 && consoleLogLevel <= logLevel)
	{
		switch(logLevel)
		{
			case COMPLETE_LOG:
				cout << "\nINF> ";
				break;
			case DEBUG_DB_LOG:
				cout << "\nDBG> ";
				break;
			case DEBUG_LOG:
				cout << "\nDBG> ";
				break;
			case DEBUG_HIGH_LOG:
				cout << "\nDBGH> ";
				break;
			case ERROR_LOG:
				cout << "\nERR> ";
				break;
			case STATUS_LOG:
				cout << "\nSTS> ";
				break;
			default:
				cout << "\n   > ";
				break;
		}
		cout << str;
		consolePrint = true;
	}
}

void LogUtility::logSafeFile(const unsigned long &logLevel, string const& str)
{
//#ifndef __DEBUG
	if (localLogLevel > 0)
	{
		if (localLogLevel <= logLevel)
			cout << "";//::LogSimplePrint(logLevel + INCREASE_LOG, str);
	}
	else
		cout << "";//::LogSimplePrint(logLevel, str);
//#endif
}

bool LogUtility::checkLogLevel(const unsigned long &logLevel)
{
	if (consoleLogLevel > 0 && consoleLogLevel <= logLevel)
		return true;
	if (configuredLogLevel == 0)
		return false;
	if (localLogLevel > 0 )
		return localLogLevel <= logLevel;
	return configuredLogLevel <= logLevel;
}

string LogUtility::logLevelToString(const unsigned long &logLevel)
{
	switch(logLevel)
	{
		case 0:
			return "NONE";
		case COMPLETE_LOG:
			return "INFO";
		case DEBUG_DB_LOG:
			return "DEBUG";
		case DEBUG_LOG:
			return "DEBUG";
		case DEBUG_HIGH_LOG:
			return "DEBUGHIGH";
		case ERROR_LOG:
			return "ERROR";
		case STATUS_LOG:
			return "STATUS";
		default:
			stringstream ss;
			ss << logLevel;
			return ss.str();
	}
}

string LogUtility::localLogLevelString()
{
	if (localLogLevel > 0 && configuredLogLevel > 0)
		return "FILE LOG LEVEL FORCED TO " + logLevelToString(localLogLevel);
	return "FILE LOG LEVEL SET TO " + logLevelToString(configuredLogLevel);
}

string LogUtility::consoleLogLevelString()
{
	return "CONSOLE LOG LEVEL SET TO " + logLevelToString(consoleLogLevel);
}

string LogUtility::generateUID()
{
	time_t rawtime;
	time (&rawtime);
	clock_t t = clock();
	while (t == clock());
	stringstream ss;
	ss << rawtime<< "-" << t;
	return ss.str();
}

//string LogUtility::now()
//{
//	time_t rawtime;
//	struct tm * timeinfo;
//	char buffer[20];
//	time (&rawtime);
//	errno_t err = localtime_s(timeinfo, &rawtime);
//	if(err>0)
//		return "";
//	strftime(buffer,20,"%Y-%m-%d %H:%M:%S",timeinfo);
//	std::string str(buffer);
//	return str;
//}
