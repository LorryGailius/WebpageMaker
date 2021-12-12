#include <user_input.h>

void getArgs(int argc, char **argv, FILE ** input)
{
    if (argc == 2)
    {
        if (!(*input = fopen(argv[1], "r")))
        {
            printf("File could not be opened!\n")
            return;
        }
    }
    else if (argc == 1)
    {
        printf("No data file name given! Check \"README.md\" for more information!\n")
        return;
    }
    else
    {
        printf("Too many arguments!\n")
        return;
    }
}