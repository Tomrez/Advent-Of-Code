#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Place
{
    char name[4];
    char left[4];
    char right[4];
};

#define START_INST "AAA"
#define END_INST "ZZZ"


int main()
{
    FILE *fp = fopen("part1.in", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Wrong input file\n");
        return 1;
    }
    char buffer[512];
    memset(buffer, '\0', 512);

    fgets(buffer, 512, fp);

    char instructions[300];
    strcpy(instructions, buffer);
    struct Place places[714];

    //Get rid of the empty line
    fgets(buffer, 512, fp);
    memset(buffer, '\0', 512);

    //Store input
    for(int i = 0; fgets(buffer, 512, fp) != NULL; i++)
    {
        strncpy(places[i].name, buffer, 3);
        strncpy(places[i].left, buffer + 7, 3);
        strncpy(places[i].right, buffer + 12, 3);
        memset(buffer, '\0', 512);
    }

    char *actualPlace = START_INST;

    int instructionPos = 0;

    int result = 0;
    while (strncmp(actualPlace, END_INST, 3))
    {
        int i = 0;
        while(strncmp(places[i].name, actualPlace, 3))
        {
            i++;
        }

        if(instructions[instructionPos] == 'L')
        {
            actualPlace = places[i].left;
        }
        else
        {
            actualPlace = places[i].right;
        }

        instructionPos = (instructionPos + 1) % (strlen(instructions)-1);
        result++;
    }

    printf("%d\n", result);

    fclose(fp);
    return 0;
}