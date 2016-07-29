#include <syslog.h>

int main()
{
	openlog("ylmlog", LOG_CONS | LOG_PID, LOG_USER);
	
	syslog(LOG_ERR, "this is an error log");
	syslog(LOG_WARNING, "this is a warning log");
	syslog(LOG_NOTICE, "this is a notice log");
	syslog(LOG_INFO, "this is an info log");
	syslog(LOG_DEBUG, "this is a debug log");
	
	closelog();
}