#include <user_input.h>
#include <assert.h>

int getInput(int argc, char **argv, data_t **data, char **title, char **desc, int *size)
{
    if (argc == 2)
    {
        FILE *input;
        input = fopen(argv[1], "r");
        if (input == NULL)
        {
            printf("File could not be opened!\n");
            return 0;
        }
        *data = (data_t *)malloc(MAX_DATA_POINTS * sizeof(data));
        readFile(input, *data, title, desc, size);
        return 1;
    }
    else if (argc == 1)
    {
        printf("No data file name given! Check \"README.md\" for more information!\n");
        return 0;
    }
    else
    {
        printf("Too many arguments!\n");
        return 0;
    }
}

void readFile(FILE *input, data_t *data, char **title, char **desc, int *size)
{
    *size = 0;
    fseek(input, 0, SEEK_END);
    size_t input_size = ftell(input);
    rewind(input);
    char buffer[input_size];
    memset(buffer, 0, input_size);
    fread(buffer, sizeof(char), input_size, input);
    char delim[] = ";\r\n";

    char *token = strtok(buffer, delim);

    // Timeline title
    if (token)
    {
        if (strcmp(token, "-") == 0)
        {
            *title = NULL;
        }
        else
        {
            *title = (char *)malloc(sizeof(char) * (strlen(token) + 1));
            if (*title == NULL)
            {
                printf("Oops! Something went wrong. Better luck next time ;)\n");
            }
            else
            {
                strcpy(*title, token);
            }
        }
        token = strtok(NULL, delim);
    }

    // Timeline description
    if (token)
    {
        
        if (strcmp(token, "-") == 0)
        {
            *desc = NULL;
        }
        else
        {
            *desc = (char *)malloc(sizeof(char) * (strlen(token) + 1));
            if (*desc == NULL)
            {
                printf("Oops! Something went wrong. Better luck next time ;)\n");
            }
            else
            {
                strcpy(*desc, token);
            }
        }
        token = strtok(NULL, delim);
    }

    for (int i = 0; token; i++)
    {
        // Date
        if (token)
        {
            if (strcmp(token, "-") == 0)
            {
                data[i].header = NULL;
            }
            else
            {
                data[i].header = (char *)malloc(sizeof(char) * (strlen(token) + 1));
                if (data[i].header == NULL)
                {
                    printf("Oops! Something went wrong. Better luck next time ;)\n");
                }
                else
                {
                    strcpy(data[i].header, token);
                }
            }
            token = strtok(NULL, delim);
        }

        //Description
        
        if (token)
        {
            if (strcmp(token, "-") == 0)
            {
                data[i].description = NULL;
            }
            else
            {
                data[i].description = (char *)malloc(sizeof(char) * (strlen(token) + 1));
                
                if (data[i].description == NULL)
                {
                    printf("Oops! Something went wrong. Better luck next time ;)\n");
                }
                else
                {
                    strcpy(data[i].description, token);
                }
            }
            
            token = strtok(NULL, delim);
        }
        //Image
        if (token)
        {
            if (strcmp(token, "-") == 0)
            {
                data[i].image = NULL;
            }
            else
            {
                data[i].image = (char *)malloc(sizeof(char) * strlen(token) + 1);
                if (data[i].image == NULL)
                {
                    printf("Oops! Something went wrong. Better luck next time ;)\n");
                }
                else
                {
                    strcpy(data[i].image, token);
                }
            }
            token = strtok(NULL, delim);
            (*size)++;
        }

    }
}

void freeInput(data_t *data, char *title, char* desc, int pointNum)
{
    if (title != NULL)
    {
        free(title);
    } 
    
    if (desc != NULL)
    {
        free(desc);
    }

    for (int i = 0; i < pointNum; ++i)
    {
        if (data[i].header != NULL)
        {
            free(data[i].header);
        }
        
        if (data[i].description != NULL)
        {
            free(data[i].description);
        }

        if (data[i].image != NULL)
        {
            free(data[i].image);
        }
        
    }
    
    if (data != NULL)
    {
        free(data);
    }
}