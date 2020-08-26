#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>

void timer_handler(int signum)
{
	static int count = 0;
	printf("Timer expired %d times\n",++count);
}

int main()
{
	struct sigaction sa;
	struct itimerval timer;

	memset(&sa,0,sizeof(sa));
	sa.sa_handler = &timer_handler;
	sigaction(SIGVTALRM,&sa,NULL);

	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec =0;

	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;

	setitimer(ITIMER_VIRTUAL,&timer,NULL);

	while(1);
}
