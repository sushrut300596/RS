#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
	int i;
	// unsigned char buffer[524288] = {0};
	unsigned char buffer = 255;
	long a = 0xffffffffffffffff;
	// int bits_in_buf = 0;
	// buffer >>= 1;
	// printf("%d\n", buffer);
	// if(1)
		// buffer |= 0x80;
	// bits_in_buf++;
	// if(bits_in_buf == 8)
		// printf("%d\n", buffer);
	// for(i = 0; i < 524288; i++) {
	// 	buffer[i] = buffer[i] | 0xff;
	// }
	// for(i = 0; i < 524288; i++) {
	// 	printf("%d ",buffer[i]);
	// }

	buffer ^= 223;
	buffer ^= 32;

	a ^= 0x0000000000000000;

	
	printf("%lx", a);
	printf("\n");
}