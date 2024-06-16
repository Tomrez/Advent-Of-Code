#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

    FILE *fp = fopen("input.in", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Wrong file\n");
        return 1;
    }

    char buffer[512];

    int topResult = 0;
    int result = 0;

    while(fgets(buffer, 512, fp) != NULL)
    {        
        if(buffer[0] == '\n')
        {
            if (topResult < result)
            {
                topResult = result;
            }
            result = 0;
        }
        else
        {
            result += atoi(buffer);
        }
    }

    printf("%d\n", topResult);

    fclose(fp);
    return 0;
}