#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

#define INTERVAL 500

/*Function prototype.*/
void DoStuff(void);

int main(int argc, char* argv[])
{
	struct itimerval it_val;	/*for setting itimer.*/

	/*Upon SIGALRM, call DoStuff().
	 * Set interval timer. we want frequency in ms,
	 * but the setitimer call needsseconds and useconds.*/
	if(signal(SIGALRM,(void(*)(int))DoStuff)==SIG_ERR)
	{
		perror("Unable to catch SIGALRM");
		exit(1);
	}
	
	it_val.it_value.tv_sec = INTERVAL/1000;
	it_val.it_value.tv_usec = (INTERVAL*1000)%1000000;
	it_val.it_interval = it_val.it_value;

	if(setitimer(ITIMER_REAL,&it_val,NULL)==-1)
	{
		perror("Error calling setitimer()\n");
		exit(1);
	}

	while(1)
	{
		pause();
	}
}

void DoStuff(void)
{
	printf("Timer went off.\n");
}
