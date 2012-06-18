#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void create_file(char *file_name)
{
	if(creat(file_name,0664) < 0)
	{
		printf("create file %s failure\n",file_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("create file %s success\n",file_name);
	}
}

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("please input two numbers");
		return EXIT_FAILURE;
	}

	create_file(argv[1]);
	return EXIT_SUCCESS;
}
