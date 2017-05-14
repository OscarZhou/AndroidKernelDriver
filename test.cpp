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
	int outfile[9] = {0};
	int result = 0;
	int i = 0;
	fd = open(DEVICENAME, O_RDONLY);
	if(fd<0)
	{
		perror("open");
		exit(1);
	}
	result = read(fd, (int*)outfile, sizeof(outfile));
	if(result<0)
	{
		perror("read");
		printf("\n");
		exit(1);
	}
	for(i=0;i<9;i++)
	{
		printf("outfile[%d] = %.4f\n", i, outfile[i]/255.00);

	}
	close(fd);
	return 0;
}
