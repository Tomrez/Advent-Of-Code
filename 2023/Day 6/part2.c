#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    FILE *fp = fopen("part1.in", "r"); 
    if (fp == NULL)
    {
        fprintf(stderr, "Wrong file\n");
        return 1;
    }

    int result = 0;

    char c;

    char numChar[20];
    memset(numChar, '\0', 20);
    int numCharPos = 0;

    long time = 0;
    long distance = 0;

    bool firstLineFlag = true;

    while ((c = fgetc(fp)) != EOF)
    {
        if (isdigit(c))
        {
            numChar[numCharPos++] = c;
        }
        else if (c == '\n' && numCharPos > 0)
        {
            numChar[numCharPos] = '\0';
            if(firstLineFlag)
            {
                time = atol(numChar);
            }
            else
            {
                distance = atol(numChar);
            }
            numCharPos = 0;
            memset(numChar, '\0', 20);

            firstLineFlag = false;
        }  
    }

    for (int j = 1; j < time; j++)
    {
        if(((time - j) * j) > distance)
        {
            result++;
        }
    }

    printf("%d\n", result);

    fclose(fp);
    return 0;
}