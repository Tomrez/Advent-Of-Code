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

    int first = 0;
    int second = 0;
    int third = 0;

    int result = 0;

    while(fgets(buffer, 512, fp) != NULL)
    {        
        if(buffer[0] == '\n')
        {
            if (result > first)
            {
                third = second;
                second = first;
                first = result;
            }
            else if (result > second)
            {
                third = second;
                second = result;
            }
            else if (result > third)
            {
                third = result;
            }
            result = 0;
        }
        else
        {
            result += atoi(buffer);
        }
    }

    printf("%d\n", first + second + third);

    fclose(fp);
    return 0;
}