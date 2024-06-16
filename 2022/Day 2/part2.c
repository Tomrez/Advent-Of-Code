#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_COUNT 2500

#define ROCKE 'A'
#define PAPERE 'B'
#define SCISSORSE 'C'

#define ROCKP 1
#define PAPERP 2
#define SCISSORSP 3

#define LOSE 'X'
#define DRAW 'Y'
#define WIN 'Z'

int whoWin(char e, char p)
{
    switch (p)
    {
        case LOSE:
            if (e == PAPERE)
                return ROCKP;
            else if (e == ROCKE)
                return SCISSORSP;
            else
                return PAPERP;
        case DRAW:
            if (e == SCISSORSE)
                return SCISSORSP;
            else if (e == PAPERE)
                return PAPERP;
            else
                return ROCKP;
        case WIN:
            if (e == ROCKE)
                return  PAPERP;
            else if (e == SCISSORSE)
                return ROCKP;
            else
                return SCISSORSP;
    }
}

int gameResult(char c)
{
    switch (c)
    {
        case WIN:
            return 6;
        case DRAW:
            return 3;
        case LOSE:
            return 0;
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
        result += whoWin(buffer[0], buffer[2]) + gameResult(buffer[2]);
    }

    printf("%d\n", result);

    fclose(fp);
    return 0;
}