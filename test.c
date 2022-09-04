#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

void readFile(int fd, int length) {
	int i = 0, n;
	unsigned char *str = malloc(length);
	if(fd != -1) {
    	n = read(fd, str, length);
    	while(i < n) {
      		printf("%x", str[i]);
      		i++;
    	}
    	printf("\n");
  	}
}

int main() {
	long a = 0x12345678a1a2a3a4;
	int length = sizeof(a);
	int fd;
	fd = open("test.txt", O_CREAT | O_WRONLY, 00700);
	write(fd, &a, length);
	close(fd);
	fd = open("test.txt", O_RDONLY);
	readFile(fd, length);
}