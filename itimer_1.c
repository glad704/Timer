#include<stdio.h>
#include<signal.h>
#include<sys/time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

static char msg[] = "Time is running out\n";
static int len;

//Output information to standard error telling user it's time
void prompt_info(int signo)
{
	write(STDERR_FILENO,msg,len);
}

//Set up signal processing mechanism
void init_sigaction(void)
{
	struct sigaction tact;

	/*Signaled to the task processing function to be executed as prompt_info*/
	tact.sa_handler = prompt_info;
	tact.sa_flags = 0;

	/*Initialize signal set*/
	sigemptyset(&tact.sa_mask);

	/*Set up signal processing mechanism*/
	sigaction(SIGALRM,&tact,NULL);
}

void init_time()
{
	struct itimerval value;

	/*Set a task execution interval of 2 seconds and 20 microseconds*/
	value.it_value.tv_sec = 2;
	value.it_value.tv_usec = 0;

	/*Set the initial time count to2 seconds 0 microseconds*/
	value.it_interval = value.it_value;

	/*Set timer ITIMER_REAL*/
	setitimer(ITIMER_REAL,&value,NULL);
}

int main()
{
	len = strlen(msg);
	init_sigaction();
	init_time();
	while(1);
	exit(0);
}
