#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

void log_info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    printf("%d-%02d-%02d %02d:%02d:%02d INFO ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    vprintf(format, args);
    printf("\n");

	fflush(stdout);

    va_end(args);
}
