#include <stdlib.h>
#include <stdio.h>

void Func(int x);

int main(int argc, char **argv) 
{
	printf("Puslapis!");
	return EXIT_SUCCESS;
}


void Func(int x)
{
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n",i);
    }
}