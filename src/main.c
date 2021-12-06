#include <stdlib.h>
#include <stdio.h>

void Func(int x);

int main(int argc, char **argv) 
{
	printf("Puslapis!");
	
    int x = 10;
    Func(x);
    
    return EXIT_SUCCESS;

}


void Func(int x)
{
    for (size_t i = 0; i < x; i++)
    {
        printf("%d\n",i);
    }
}