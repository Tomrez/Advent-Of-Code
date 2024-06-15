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

    int result = 1;

    char c;
    char numChar[10];
    memset(numChar, '\0', 10);
    int numCharPos = 0;

    int timeArray[100];
    memset(timeArray, '\0', 100*sizeof(int));
    int timeArrayPos = 0;
    int distanceArray[100];
    memset(distanceArray, '\0', 100*sizeof(int));
    int distanceArrayPos = 0;

    bool firstLineFlag = true;

    while ((c = fgetc(fp)) != EOF)
    {
        if (isdigit(c))
        {
            numChar[numCharPos++] = c;
        }
        else if ((!isdigit(c)) && numCharPos > 0)
        {
            numChar[numCharPos] = '\0';
            if(firstLineFlag)
            {
                timeArray[timeArrayPos++] = atoi(numChar);
            }
            else
            {
                distanceArray[distanceArrayPos++] = atoi(numChar);
            }
            numCharPos = 0;
            memset(numChar, '\0', 10);
        }  
        if (c == '\n')
        {
            firstLineFlag = false;
        }
    }
    distanceArray[distanceArrayPos] = '\0';
    timeArray[timeArrayPos] = '\0';

    for(int i = 0; i < 4; i++)
    {
        int dist = distanceArray[i];
        int time = timeArray[i];

        int options = 0;

        for (int j = 1; j < time; j++)
        {
            if(((time - j) * j) > dist)
            {
                options++;
            }
        }
        result = result * options;
    }

    printf("%d\n", result);

    fclose(fp);
    return 0;
}