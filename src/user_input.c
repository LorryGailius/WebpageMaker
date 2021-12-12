#include <user_input.h>

void getInput(int argc, char **argv, data_t **data, char **title, char **desc, int *size)
{
    if (argc == 2)
    {
        FILE *input;
        input = fopen(argv[1], "r");
        if (input == NULL)
        {
            printf("File could not be opened!\n");
            return;
        }
        *data = (data_t *)malloc(MAX_DATA_POINTS * sizeof(data));
        readFile(input, *data, title, desc, size);
    }
    else if (argc == 1)
    {
        printf("No data file name given! Check \"README.md\" for more information!\n");
        return;
    }
    else
    {
        printf("Too many arguments!\n");
        return;
    }
}

void readFile(FILE *input, data_t *data, char **title, char **desc, int *size)
{
    *size = 0;
    fseek(input, 0, SEEK_END);
    size_t input_size = ftell(input);
    rewind(input);
    char buffer[input_size];
    fread(buffer, sizeof(char), input_size, input);
    char delim[] = ";\r\n";

    char *token = strtok(buffer, delim);

    // Timeline title
    if (token)
    {
        *title = (char *)malloc(sizeof(char) * strlen(token));
        if (strcmp(*title, "-") == 0)
        {
            *title = NULL;
        }
        else
        {
            strcpy(*title,token);
        }
        token = strtok(NULL, delim);
    }

    // Timeline description
    if (token)
    {
        *desc = (char *)malloc(sizeof(char) * strlen(token));
        if (strcmp(*desc, "-") == 0)
        {
            *desc = NULL;
        }
        else
        {
            strcpy(*desc,token);
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
                data[i].header = (char *)malloc(sizeof(char) * strlen(token));
                strcpy(data[i].header, token);
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
                data[i].description = (char *)malloc(sizeof(char) * strlen(token));
                strcpy(data[i].description, token);
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
                data[i].image = (char *)malloc(sizeof(char) * strlen(token));
                strcpy(data[i].image, token);
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