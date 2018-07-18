#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>

int main()
{
	char value[24];
	printf("Listing all the files.)");
	system("ps ax ");
	//1

	printf("enter seconds to sleep this system.");
	scanf("%s",value);
	//2
	//convert
	int sleepTime = atoi(value);
	//3

	//4
	sleep(sleepTime);

	//5
	thisUID = getuid();//get PID
	printf("THis UID is: %d",thisUID);
	return 0;
}
