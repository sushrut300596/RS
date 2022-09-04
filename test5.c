#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void readWrite(int fd, int fd1) {
	int i, n, arrlength;
	unsigned char *str = malloc(25);
	if(fd != -1) {
    	n = read(fd, str, sizeof(int));
    	arrlength = *(int *)str;
    	write(fd1, &arrlength, sizeof(int));
    	// void *temp[arrlength];
    	int strlength[arrlength];
    	char *temp[arrlength];
    	for(i = 0; i < arrlength; i++) {
    		n = read(fd, str, sizeof(int));
    		strlength[i] = *(int *)str;
    	}
    	for(i = 0; i < arrlength; i++) {
    		str = malloc(strlength[i]);
    		temp[i] = malloc(strlength[i]);
    		n = read(fd, str, strlength[i]);
    		strcat(temp[i], str);
    	}
    	for(i = 0; i < arrlength; i++) {
    		write(fd1, &strlength[i], sizeof(int));
    		write(fd1, temp[i], strlength[i]);
    	}
  	}
}

int main() {
	int fd, fd1;
	fd = open("char_test1.txt", O_RDONLY);
	fd1 = open("char_test3.txt", O_CREAT | O_WRONLY, 00700);
	readWrite(fd, fd1);
	close(fd);
	close(fd1);
}