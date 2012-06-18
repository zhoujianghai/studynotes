#include <stdio.h>


void file_copy(FILE *in,FILE *out)
{
	int c;
	while((c = getc(in)) != EOF)
	{
		putc(c,out);	
	}
}

int main(int argc,char **argv)
 {
	FILE* in;
	if(argc == 1)
	{
		file_copy(stdin,stdout);	
		return 0;
	}

	while(--argc > 0)
	{
		if((in = fopen(*++argv,"r")) == NULL )	
		{
			printf("open file %s error\n",*argv);	
			  return 1;
		}
		else 
		{
			file_copy(in,stdout);	
			fclose(in);
		}
	}

	return 0;
 }
