#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<sys/time.h>

unsigned int x = 0;

void interrupt(int signum)
{
	printf("Timer %d!\n",++x);
}

int main()
{
	struct sigaction sa;
	struct itimerval timer;

	memset(&sa,0,sizeof(sa));
	sa.sa_handler = &interrupt;
	sigaction(SIGPROF,&sa,NULL);

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 5000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 500000;

	setitimer(ITIMER_PROF,&timer,NULL);

	for(;;);

	return 0;

}
