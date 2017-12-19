#include <stdio.h>
#include <stdlib.h>
int main() {
unsigned int c = 'z';
printf("%x\n", c & 0xff);   
printf("%x\n", (unsigned char) c);

unsigned char d = 'z';
printf("%hhx\n", d);

}