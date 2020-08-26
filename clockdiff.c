#include<stdio.h>
#include<time.h>

int main()
{
	int i;
	time_t start,end;
	start = time(NULL);
	scanf("%d",&i);
	end = time(NULL);

	printf("The time difference was %f seconds\n",difftime(end,start));

	return 0;
}
