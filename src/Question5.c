#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//Attemp an opening
	int openFile = open("/dev/memory", O_RDWR | O_NONBLOCK);
	//Write to device
	ssize_t writeTest = write(openFile, "Ross", 1);
	char bufferStatus[1];
	//Read 
	ssize_t readTest = read(openFile, bufferStatus, 1);
	//Close file/device
	close(openFile);
	printf("%s\n", bufferStatus);
}