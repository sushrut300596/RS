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
    	printf("%d\n", n);
    	while(i < length) {
      		printf("%x", str[i]);
   			i++;
   			if(i %8 == 0)
   				printf("\n");
    	}
    	printf("\n");
  	}
}

int main() {
	char ch = ' ';
	long a[] = {0x12345678a1a2a3a4, 0x45617234a2a1a5a6, 0x14236785a1a2a4a6, 0x24356718a6a7a8a9, 0x12435364a1a2a3a4, 0x43218765a7a5a4a3, 0x54672341b1b2b3b4, 0x87456732b2b3b4b5};
	int length = sizeof(a);
	int n = sizeof(a)/sizeof(long);
	printf("%d\n%d\n", length, n);
	int fd;
	fd = open("test_arr.txt", O_CREAT | O_WRONLY, 00700);
	for(int i = 0; i < n; i++) {
		write(fd, &a[i], 8);
	}
	close(fd);
	fd = open("test_arr.txt", O_RDONLY);
	readFile(fd, length);
}