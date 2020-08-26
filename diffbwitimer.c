#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<string.h>
#include<stdbool.h>

//ms
#define TIMEOUT (50)

//Type of timer
#define TIMER_TYPE ITIMER_VIRTUAL

int timer_signal(int timer_type)
{
	int sig;
	switch(timer_type)
	{
		case ITIMER_REAL:
			sig = SIGALRM;
			break;
		case ITIMER_VIRTUAL:
			sig = SIGVTALRM;
			break;
		case ITIMER_PROF:
			sig = SIGPROF;
			break;
		default:
			fprintf(stderr,"ERROR: unknown timer type %d!\n",timer_type);
			exit(EXIT_FAILURE);
	}
	return sig;
}

void set_timer(int type,void (*handler)(int),int ms)
{
	struct itimerval timer;
	struct sigaction sa;

	/*Install signal handler for the timer.*/
	memset(&sa,0,sizeof(sa));
	sa.sa_handler = handler;
	sigaction(timer_signal(type),&sa,NULL);

	/*Configure the timer to expire after ms msec...*/
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = ms*1000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 0;

	if(setitimer(type,&timer,NULL)<0)
	{
		perror("Setting timer");
		exit(EXIT_FAILURE);
	};
}

/*Timer signal handler*/
void timer_handler(int signum)
{
	static int count = 0;
	fprintf(stderr,"======> timer (%03d)\n",count++);
	set_timer(TIMER_TYPE,timer_handler,TIMEOUT);
}

/*Calculate the nth Fibonacci number using recursion.*/
int fib(int n)
{
	switch(n)
	{
		case 0:
			return 0;
		case 1:
			return 1;
		default:
			return fib(n-1)+fib(n-2);
	}
}

/*Print the Fibonacci number sequence over and over again.
 * This is deliberately an unnecessary slow and cpu intensive 
 * implementation where each number in the sequence is calculated
 * recursively from scratch.*/
void fibonacci_fast()
{
	int a = 0;
	int b = 1;
	int n = 0;
	int next = a+b;

	while(true)
	{
		printf(" fib(%d) =%d\n",n,a);
		next = a+b;
		a = b;
		b = next;
		n++;
		if(next<0)
		{
			a = 0;
			b = 1;
			n = 0;
		}
	}
}

int main()
{
	/*Flush each printf() as it happens.*/
	setvbuf(stdout,0,_IOLBF,0);
	setvbuf(stderr,0,_IOLBF,0);

	set_timer(TIMER_TYPE,timer_handler,TIMEOUT);

	//Call fibonacci_fast() or fibonacci_slow()
	
	fibonacci_fast();
	//fibonacci_slow();
}