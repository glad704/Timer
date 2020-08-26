#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include<string.h>

void time_handler(int signum)	//function handler
{
	struct timeval start;	//creating an object of type timeval to access various timer parameter
	gettimeofday(&start,NULL);	//get current time of day in object start
	printf("Timer_handler at time = %lu \n",1000000*(start.tv_sec)+start.tv_usec);
}

int main()
{
	struct sigaction sa;	//creating an object of type sigaction used to handle interrupt
	memset(&sa,0,sizeof(sa));	
	struct itimerval timer;		//creating an object of type itimerval used to set timer values
	sa.sa_handler = &time_handler;	//set the function handler
	sigaction(SIGALRM,&sa,NULL);	//call the sigaction with sa structure
	
	//configure timer parameters for 5 seconds//
	timer.it_value.tv_sec = 5;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 5;
	timer.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL,&timer,NULL);	//call the setitimer with timer structure

	for(;;);	//run the program forever
}
