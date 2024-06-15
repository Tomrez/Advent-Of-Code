#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int getFirstNum(char *line)
{
    for (int i = 0; i < strlen(line); i++)
    {
        if (isdigit(line[i]))
        {
            return line[i] - '0';
        }
    }
    return 0;
}


int getLastNum(char *line)
{
    for (int i = strlen(line) - 1; i >= 0; i--)
    {
        if (isdigit(line[i]))
        {
            return line[i] - '0';
        }
    }
    return 0;
}


int main()
{
    FILE *fp = fopen("./part1.in", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error when opening file\n");
        return 1;
    }

    char buff[512];
    memset(buff, '\n', 512);

    int result = 0;

    while (fgets(buff, sizeof(buff), fp) != NULL)
    {
        result += (10*getFirstNum(buff)) + getLastNum(buff);

        memset(buff, '\n', 512);
    }

    printf("Result: %d\n", result);

    fclose(fp);
    return 0;
}