#include<stdio.h>
#include<time.h>
void display()
{
        printf("Elapsed time was %ld secs.\n",clock()/CLOCKS_PER_SEC);
}
int main()
{
	getchar();
	display();

	getchar();
	display();

	return 0;
}


