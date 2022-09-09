#include <stdio.h>

int main() {
	int a = 0xffff;
	a >>= 13;
	printf("%x\n", a);
}