#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


char* numArray[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int getFirstNum(char *line)
{
    int intPos = -1;
    int charPos = -1;

    int intRes = -1;
    int charRes = -1;

    for (int i = 0; i < strlen(line); i++)
    {
        if (isdigit(line[i]))
        {
            intRes = line[i] - '0';
            intPos = i;
            break;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        char *result = strstr(line, numArray[i]);
        if (result != NULL)
        {
            if (charPos == -1)
            {
                charPos = result - line;
                charRes = i + 1;
            }
            else
            {
                if(charPos > (result - line))
                {
                    charPos = result - line;
                    charRes = i + 1;
                }
            }
        }
    }

    if (charPos == -1)
        return intRes;
    else if (intPos == -1)
        return charRes;

    if (charPos > intPos)
        return intRes;
    else if (charPos < intPos)
        return charRes;
    else
        return 0;

}

int getLastNum(char *line)
{
    int intPos = -1;
    int charPos = -1;

    int intRes = -1;
    int charRes = -1;

    for (int i = strlen(line) - 1; i >= 0; i--)
    {
        if (isdigit(line[i]))
        {
            intRes = line[i] - '0';
            intPos = i;
            break;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        char *curr = line;
        char *last = NULL;

        while ((curr = strstr(curr, numArray[i])) != NULL)
        {
            last = curr;
            curr++;
        }
        if (last != NULL && charPos < (last - line))
        {
            charPos = last - line;
            charRes = i + 1;
        }
    }

    if (charPos == -1)
        return intRes;
    else if (intPos == -1)
        return charRes;

    if (charPos < intPos)
        return intRes;
    else if (charPos > intPos)
        return charRes;
    else
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