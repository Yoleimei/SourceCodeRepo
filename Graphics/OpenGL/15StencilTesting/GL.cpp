#include "GL.h"

static char buffer[2048] = { 0 };
static std::mutex logMutex;

const char GL_LOG_LEVEL_ERROR[]   = "ERR ";
const char GL_LOG_LEVEL_WARNING[] = "WARN";
const char GL_LOG_LEVEL_INFO[]    = "INFO";
const char GL_LOG_LEVEL_DEBUG[]   = "DBG ";

void glPrintNull(const char* const, ...)
{
}

void glPrintError(const char* const fmt, ...)
{
	logMutex.lock();

	memset(buffer, 0, sizeof(buffer));
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsprintf_s(buffer, fmt, argptr);
	va_end(argptr);
	printf("%s: %s", GL_LOG_LEVEL_ERROR, buffer);

	logMutex.unlock();
}

void glPrintWarning(const char* const fmt, ...)
{
	logMutex.lock();

	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsprintf_s(buffer, fmt, argptr);
	va_end(argptr);
	printf("%s: %s", GL_LOG_LEVEL_WARNING, buffer);

	logMutex.unlock();
}

void glPrintInfo(const char* const fmt, ...)
{
	logMutex.lock();

	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsprintf_s(buffer, fmt, argptr);
	va_end(argptr);
	printf("%s: %s", GL_LOG_LEVEL_INFO, buffer);

	logMutex.unlock();
}

void glPrintDebug(const char* const fmt, ...)
{
	logMutex.lock();

	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vsprintf_s(buffer, fmt, argptr);
	va_end(argptr);
	printf("%s: %s", GL_LOG_LEVEL_DEBUG, buffer);

	logMutex.unlock();
}
