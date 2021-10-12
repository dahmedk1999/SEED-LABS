#include <stdio.h>
#include <stdlib.h>
#define LEN 32 // 256 bits
int main()
{
    unsigned char *key = (unsigned char *)malloc(sizeof(unsigned char) * LEN);
    FILE *random = fopen("/dev/urandom", "r");
    fread(key, sizeof(unsigned char) * LEN, 1, random);
    int i=0;
    while(i<sizeof(key))
    {
    printf("%.2x", (unsigned char)key[i]);//output byte by byte
    i++;
    }
    printf("\n");//cleanup
    fclose(random);
}