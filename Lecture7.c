#include <stdio.h>

extern int randperm(int *, int );

int main(int argc, char *argv[]){
        int some_array[52], i;

        for(i = 0; i < 52; i++)
                some_array[i] = i;

        printf("****************Before*****************\n");
        for(i = 0; i < 52; i++)
                printf("%d ", some_array[i]);

        i = randperm(some_array, 52);

        printf("\n****************After****************\n");
        for(i = 0; i< 52; i++)
                printf("%d ", some_array[i]);
}