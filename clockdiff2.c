#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>
void funExit()
{
	printf("FunExit()\n");
	printf("Press key for exit this function\n");
	while(1)
	{
		if(getchar())
		{
			break;
		}
	}
	printf("Exit\n");
}

int main()
{
	clock_t time1;
	time1 = clock();
	funExit();
	time1 = clock()-time1;
	double time_taken = ((double)time1)/CLOCKS_PER_SEC;
	printf("Function Exit took %f sec\n",time_taken);
}
