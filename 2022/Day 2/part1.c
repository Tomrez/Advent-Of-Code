#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_COUNT 2500

#define ROCKE 'A'
#define PAPERE 'B'
#define SCISSORSE 'C'

#define ROCKP 'X'
#define PAPERP 'Y'
#define SCISSORSP 'Z'

int whoWin(char e, char p)
{
    switch (p)
    {
        case ROCKP:
            if (e == PAPERE)
                return 0;
            else if (e == ROCKE)
                return 3;
            else
                return 6;
        case PAPERP:
            if (e == SCISSORSE)
                return 0;
            else if (e == PAPERE)
                return 3;
            else
                return 6;
        case SCISSORSP:
            if (e == ROCKE)
                return 0;
            else if (e == SCISSORSE)
                return 3;
            else
                return 6;
    }
}

int itemValue(char c)
{
    switch (c)
    {
        case ROCKP:
            return 1;
        case PAPERP:
            return 2;
        case SCISSORSP:
            return 3;
    }
}

int main()
{
    FILE *fp = fopen("input.in", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Wrong file\n");
        return 1;
    }

    int result = 0;

    char buffer[512];

    for (int i = 0; fgets(buffer, 512, fp) != NULL; i++)
    {
        result += whoWin(buffer[0], buffer[2]) + itemValue(buffer[2]);
    }

    printf("%d\n", result);

    fclose(fp);
    return 0;
}