#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void readFile(int fd) {
	int i, n, arrlength;
	unsigned char *str = malloc(10);
	if(fd != -1) {
    	n = read(fd, str, sizeof(int));
    	arrlength = *(int *)str;
    	printf("%d ", arrlength);
    	int strlength[arrlength];
    	for(i = 0; i < arrlength; i++) {
    		n = read(fd, str, sizeof(int));
    		strlength[i] = *(int *)str;
    		printf("%d ", strlength[i]);
    	}
    	for(i = 0; i < arrlength; i++) {
    		str = malloc(strlength[i]);
    		n = read(fd, str, strlength[i]);
    		printf("%s", str);
    	}
    	printf("\n");
  	}
}

int main() {
	char *str[4] = {"How ", "you ", "Doing", "!!"};
	int n = 4;
	int i, length;
	int fd;
	fd = open("char_test1.txt", O_CREAT | O_WRONLY, 00700);
	write(fd, &n, sizeof(n));
	for(i = 0; i < n; i++) {
		length = strlen(str[i]);
		write(fd, &length, sizeof(length));
	}
	for(i = 0; i < n; i++) {
		length = strlen(str[i]);
		write(fd, str[i], length);
	}
	close(fd);
	fd = open("char_test1.txt", O_RDONLY);
	readFile(fd);
}