#include <time.h>
#include <stdio.h>

int main(void)
{
	struct tm *p;
	time_t t;
//get time
	time(&t);
	p = localtime(&t);

	printf("%s\n",asctime(p));
	printf("%s\n",ctime(&t));

	return 0;
}
