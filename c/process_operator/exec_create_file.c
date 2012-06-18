#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//execl create file
int main(int argc,char *argv[])
{
	if(argc < 2) return EXIT_FAILURE;
	if(execl("../file_operator/file_create","file_create",argv[1],NULL) < 0)
		perror("execl error");
return EXIT_SUCCESS;
}
