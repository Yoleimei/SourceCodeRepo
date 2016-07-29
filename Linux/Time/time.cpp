#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
  
/**
 * struct timeval {
 *     time_t      tv_sec;     // seconds 
 *     suseconds_t tv_usec;    // microseconds
 * };
 *
 * struct timezone {
 *    int tz_minuteswest;     // minutes west of Greenwich 
 *    int tz_dsttime;         // type of DST correction 
 * };
 */

/**
 * 01. (2) int gettimeofday(struct timeval *tv, struct timezone *tz);
 * 02. (2) time_t time(time_t *t);
 * 03. (3) char *ctime(const time_t *timep);
 * 04. (3) struct tm *gmtime(const time_t *timep);
 * 05. (3) struct tm *localtime(const time_t *timep);
 * 06. (3) time_t mktime(struct tm *tm);
 * 07. (3) char *asctime(const struct tm *tm);
 */  

int main()
{
	struct timeval tv;
	time_t t;
	struct tm *gm_tm, *local_tm;
	
	gettimeofday(&tv, NULL);
	printf("tv_sec: %ld, tv_usec: %ld\n", tv.tv_sec, tv.tv_usec);
	time(&t);
	printf("second: %ld\n", t);
	
	printf("ctime: %s", ctime(&t));
	gm_tm = gmtime(&t);
	local_tm = localtime(&t);
	printf("compare gmtime with localtime: %d\n", memcmp(gm_tm, local_tm, sizeof(struct tm)));
	printf("year: %d (1900 plused)\n", gm_tm->tm_year + 1900);
	printf("month: %d\n",       gm_tm->tm_mon);
	printf("day: %d\n",         gm_tm->tm_mday);
	printf("hour: %d\n",        gm_tm->tm_hour);
	printf("minute: %d\n",      gm_tm->tm_min);
	printf("second: %d\n",      gm_tm->tm_sec);
	printf("day of week: %d\n", gm_tm->tm_wday);
	printf("day of year: %d\n", gm_tm->tm_yday);
	
	printf("mktime: %ld\n", mktime(gm_tm));
	printf("asctime: %s", asctime(gm_tm));
}
