#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>


/**********************************************************/
/*                     written by Hongyu ZHOU
/*				16242950

/*Compile: 
	arm-none-linux-gnueabi-gcc -static test.cpp -o test
/*Move executable file to device:  
	./adb push ~/Downloads/test /dev
/*Execute test program:	   
	.test
/**********************************************************/


#define DEVICENAME	"/dev/goldfish_sensor"
int main()
{
	static int fd = -1;
	char outfile[256] = {0};

	int infile = 2;
	int result = 0;
	int i = 0;
	fd = open(DEVICENAME, O_RDWR);
	if(fd<0)
	{
		perror("open");
		exit(1);
	}
	result = read(fd, (char*)outfile, sizeof(outfile));
	if(result<0)
	{
		perror("read error 1");
		printf("\n");
		exit(1);
	}
	printf("outfile = %s\n", outfile);

	result = write(fd, &infile, sizeof(infile));
	printf("-------------inputfile= %d\n!", infile);
	if(result<0)
	{
		perror("write error 2");
		printf("\n");
		exit(1);
	}
	result = read(fd, (char*)outfile, sizeof(outfile));
	if(result<0)
	{
		perror("read error 1");
		printf("\n");
		exit(1);
	}
	printf("outfile = %s\n", outfile);
	
	
	close(fd);
	return 0;
}
