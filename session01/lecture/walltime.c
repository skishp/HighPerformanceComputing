#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>

/*return real time in seconds since start of the process*/

double walltime(){
    static clock_t ticks_per_second = 0;
    if(!ticks_per_second){
        ticks_per_second = sysconf(_SC_CLK_TCK);
    }
    struct tms timebuf;
    /*times returns the number of real time ticks passed since start*/
    return (double) times(&timebuf)/ticks_per_second;
}

int main(){
    double t0 = walltime();
    sleep(2);
    double t1= walltime()-t0;
    printf("sleep(1) took actually %.4lf seconds\n",t1);
}