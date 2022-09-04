#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void readWrite(int fd, int fd1) {
	int i, j = 0, n, size, arrlength = 0, count = 0;
	if(fd != -1) {
    	size = lseek(fd, 0, SEEK_END);
    	// printf("%d\n", size);
    	unsigned char *str = malloc(size * sizeof(char));
    	lseek(fd, 0, SEEK_SET);
    	n = read(fd, str, size);
    	for(i = 0; i <= size; i++) {
    		if(str[i] == '\n') {
    			arrlength++;
    		}
    		else if(str[i] == 0) {
    			arrlength++;
    		}
    		else {}
    	}
    	// printf("%s\n", str);
    	// printf("arrl = %d\n", arrlength);
    	int strlength[arrlength];
    	for(i = 0; i <= size; i++) {
    		if(str[i] == '\n') {
    			strlength[j] = count;
    			count = 0;
    			j++;
    		}
    		else if(str[i] == 0) {
    			strlength[j] = count;
    			count = 0;
    			j++;
    		}
    		else {
    			count++;
    		}
    	}
    	// printf("%s\n", str);
    	write(fd1, &arrlength, sizeof(int));
    	for(i = 0; i < arrlength; i++) {
    		write(fd1, &strlength[i], sizeof(int));
    		write(fd1, str, strlength[i]);
    		str = str + strlength[i] + 1;
    	}
    	/*for(i = 0; i < arrlength; i++) {
    		printf("l = %d\n", strlength[i]);
    	}*/
    	// printf("%s\n", str);
  	}
}

int main() {
	int fd, fd1;
	fd = open("input.txt", O_RDONLY);
	fd1 = open("char_test4.txt", O_CREAT | O_WRONLY, 00700);
	readWrite(fd, fd1);
	close(fd);
	close(fd1);
}