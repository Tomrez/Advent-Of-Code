#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define LAST_LINE 139
#define LAST_CHAR 140

int main()
{
    FILE *fp = fopen("./part1.in", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Wrong input file");
        return 1;
    }
    
    char *array[150];

    int x = 0;

    char buffer[256];

    while(fgets(buffer, 256, fp) != NULL)
    {
        array[x] = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(array[x], buffer);
        array[x][strlen(buffer)] = '\0';
        x++;
    }

    int result = 0;
    
    int y = 0;
    while (y <= LAST_LINE)
    {
        for (x = 0; array[y][x] != '\0'; x++)
        {
            if (isdigit(array[y][x]))
            {
                bool specChar = false;
                int xStart = x;
                
                while(isdigit(array[y][++x]));

                int numLength = x - xStart;

                char charNumber[10];
                memset(charNumber, '\0', 10);

                //Vratim se pred nalezene cislo
                x = x - numLength;

                for (int i = 0; i < numLength; i++)
                {
                    charNumber[i] = array[y][x + i];
                }
                int intNumber = atoi(charNumber);

                //Radek nad
                if (y != 0)
                {   
                    int xLeftBorder;
                    if (x == 0)
                        xLeftBorder = 0;
                    else
                        xLeftBorder = x - 1;

                    int xRightBorder;
                    if (x + numLength >= LAST_CHAR)
                        xRightBorder = LAST_CHAR - 1;
                    else
                        xRightBorder = x + numLength;

                    for (int j = xLeftBorder; j <= xRightBorder; j++)
                    {
                        if (array[y - 1][j] != '.' && !isdigit(array[y - 1][j]))
                        {
                            specChar = true;
                            break;
                        }
                    }
                }
                //Radek pod
                if (y != LAST_LINE && specChar == false)
                {
                    int xLeftBorder;
                    if (x == 0)
                        xLeftBorder = 0;
                    else
                        xLeftBorder = x - 1;

                    int xRightBorder;
                    if (x + numLength >= LAST_CHAR)
                        xRightBorder = LAST_CHAR - 1;
                    else
                        xRightBorder = x + numLength;

                    for (int j = xLeftBorder; j <= xRightBorder; j++)
                    {
                        if (array[y + 1][j] != '.' && !isdigit(array[y + 1][j]))
                        {
                            specChar = true;
                            break;
                        }
                    }
                }

                //Policko vlevo
                if (x != 0 && specChar == false)
                {
                    if (array[y][x - 1] != '.' && !isdigit(array[y][x - 1]))
                    {
                        specChar = true;
                    }
                }

                //Policko vpravo
                if (x + numLength != LAST_CHAR && specChar == false)
                {
                    if (array[y][x + numLength] != '.' && !isdigit(array[y][x + numLength]))
                    {
                        specChar = true;
                    }
                }

                //Posun na posledni znak zpracovavaneho cisla -> po konci for se x inkrementuje za ono cislo
                x = x + numLength - 1;

                if (specChar == true)
                {
                    result += intNumber;
                }
            }
        }
        y++;
    }
    printf("%d\n", result);

    for (int i = 0; i < LAST_LINE; i++)
    {
        free(array[i]);
    }


    fclose(fp);
    return 0;
}