#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "math.h"

#define BUFSIZE (1024*1024)

char *filename;
int file_size;

void addFile(char *vdName, char *filename, int file_size, char *content) {
	int d = open(vdName, O_RDONLY);
	unsigned char *buf = malloc(sizeof(unsigned char) * BUFSIZE);
	if(d != -1) {
		int i = 0;
		int n, count = 0;
		n = read(d, buf, 16);
		while(count != SIZE) {
			n = read(fd, buf, buf_size);
			while(i < buf_size) {
				// code
			}
			count = count + n;
		}
	}
}

int main(int argc, char **argv) {

	char content[file_size];
	char ch;

	int a;
	while(1)
	{
		printf("\n-----------------------------------------------------------------\n1. Press 1 to Write a File.\n2. Press 2 to Read a File.\n3. Press 3 to Remove a File.\n4. Press 4 to EXIT.\n");
		printf("Enter a No. \t:\t");
		scanf("%d", &a);

		if (a == 1)
		{
			printf("Enter Filename \t:\t");
			ch = getchar();
			scanf("%[^\n]", filename);
			
			printf("Enter the size of File in bytes \t:\t");
			scanf("%d", &file_size);
			
			printf("Enter Contain \t:\t");
			ch = getchar();
			scanf("%[^\n]", content);

			addFile(argv[1], filename, file_size, content);

			// printf("%s\n", filename);
			// printf("%s\n", contain);
			// sender(remotePort, messageStr, sendfile, 0);
		}
		else if(a == 2)
		{
			// receive(receivefile);
		}
		else if (a == 3)
		{
			
		}
		else if (a == 4)
		{
			break;
		}
		else
		{
			printf("Incorrect Input.\n");
		}
	}
}