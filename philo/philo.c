#include "philo.h"

int main(int ac,char **av)
{
    (void)av;
    if(ac < 5)
    {
        printf("number of arg invalid");
        return 1;
    }
    if(check_argument(ac,av) == NULL)
        return (1);

    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv,&tz);

    printf("Seconds since 1/1/1970: %lu\n",tv.tv_sec);
    printf("Microseconds: %ld\n",tv.tv_usec);
    printf("Minutes west of Greenwich: %d\n",tz.tz_minuteswest);
    printf("Daylight Saving Time adjustment: %d\n",tz.tz_dsttime);
}