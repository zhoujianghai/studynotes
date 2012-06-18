#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		printf("please inout correct params!");
		exit(EXIT_FAILURE);
	}

	FILE *from = NULL;
	FILE *to = NULL;
	char buffer[BUFFER_SIZE];
	long file_length = 0;
//r:read,b:binary file
	if((from = fopen(argv[1],"rb")) == NULL)
	{
		printf("open file %s error!\n",argv[1]);
		exit(EXIT_FAILURE);
	}
//if the file not exist,will create new file
	if((to = fopen(argv[2],"wb")) == NULL)
	{
		printf("open file %s error!\n",argv[2]);
		exit(EXIT_FAILURE);
	}

//seek the position to the end of file
	fseek(from,0L,SEEK_END);
	//return the current position
	file_length = ftell(from);
	//seek the position to the head of file
	fseek(from,0L,SEEK_SET);
	printf("from file size is %ld\n",file_length);

	while( !feof(from) )
	{
		//read the size of BUFFER_SIZE*1 from the from file
		fread(buffer,BUFFER_SIZE,1,from);
		if(BUFFER_SIZE > file_length)
		{
			fwrite(buffer,file_length,1,to);
		}
		else
		{
			fwrite(buffer,BUFFER_SIZE,1,to);
			file_length = file_length - BUFFER_SIZE;
		}
		//clear the buffer
		bzero(buffer,BUFFER_SIZE);
	}

	fclose(from);
	fclose(to);
	return EXIT_SUCCESS;
}
