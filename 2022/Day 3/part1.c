#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define UPPER 27
#define LOWER 1


int charVal(char c)
{
    if (isupper(c))
    {
        return UPPER + (c - 'A');
    }
    else if (islower(c))
    {
        return LOWER + (c - 'a');
    }
    else
    {
        exit(1);
    }
}

int main()
{
    FILE *fp = fopen("input.in", "r");
    if (fp == NULL)
    {
        return 1;
    }

    char buffer[256];
    memset(buffer, '\0', 256);

    int result = 0;

    while (fgets(buffer, 256, fp) != NULL)
    {
        char part1[128];
        memset(part1, '\0', 128);
        strncpy(part1, buffer, strlen(buffer)/2);
        char part2[128];
        memset(part2, '\0', 128);
        strncpy(part2, buffer + strlen(buffer)/2, strlen(buffer)/2);

        bool breakFlag = false;

        for (int i = 0; i < strlen(buffer)/2; i++)
        {
            for (int j = 0; j < strlen(buffer)/2; j++)
            {
                if (part1[i] == part2[j])
                {
                    result += charVal(part1[i]);
                    breakFlag = true;
                    break;
                }
            }
            if (breakFlag)
            {
                break;
            }
        }
        memset(buffer, '\0', 256);
    }

    printf("%d\n", result);
    
    fclose(fp);
    return 0;
}