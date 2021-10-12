#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEYSIZE 16
void main()
{
    int count=0;
    int twohourwindow=1524013729;
    int creationtime=1524020929;
    int i;
    char key[KEYSIZE];
    FILE *fptrKeys;
    fptrKeys=fopen("Keys.txt","rw");
    for(int B=twohourwindow;B<=creationtime;B++)
    {
        srand(B);
        printf("Key %d for timestamp %lld :",count,B);
        for (i = 0; i < KEYSIZE; i++)
        {
            key[i] = rand() % 256;
            printf("%.2x", (unsigned char)key[i]);
            fprintf(fptrKeys,"%.2x",(unsigned char)key[i]);
        }
        printf("\n");
        fprintf(fptrKeys,"\n");
        count++;
    }
    fclose(fptrKeys);

}