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
    int y = 0;

    char buffer[256];

    while(fgets(buffer, 256, fp) != NULL)
    {
        array[x] = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(array[x], buffer);
        array[x][strlen(buffer)] = '\0';
        x++;
    }

    int starArray[150][150];
    memset(starArray, 0, 140*141);

    for (int y = 0; y < LAST_LINE; y++)
    {
        for (int x = 0; x < LAST_CHAR; x++)
        {
            if (array[y][x] == '*')
            {
                starArray[y][x] = 1;
            }
            if (array[y][x] == '\0')
            {
                starArray[y][x] = '\0';
            }
        }
    }

    int result = 0;

    for (y = 0; y <= LAST_LINE; y++)
    {
        for (x = 0; array[y][x] != '\0'; x++)
        {
            if (starArray[y][x] > 0)
            {
                //Radek nad
                if (y != 0)
                {
                    int leftX;
                    if (x == 0)
                        leftX = x;
                    else
                        leftX = x - 1;

                    if (isdigit(array[y - 1][leftX]))
                    {
                        starArray[y][x]++;
                        if(!isdigit(array[y - 1][leftX + 1]) && isdigit(array[y - 1][leftX + 2]) && x != 0)
                        {
                            starArray[y][x]++;
                        }
                    }
                    else if (isdigit(array[y - 1][leftX + 1]))
                    {
                        starArray[y][x]++;
                    }
                    else if (x != 0 && isdigit(array[y - 1][leftX + 2]) && !isdigit(array[y - 1][leftX + 1]))
                    {
                        starArray[y][x]++;
                    }
                }

                //Radek pod
                if (y != LAST_CHAR)
                {
                    int leftX;
                    if (x == 0)
                        leftX = x;
                    else
                        leftX = x - 1;

                    if (isdigit(array[y + 1][leftX]))
                    {
                        starArray[y][x]++;
                        if(!isdigit(array[y + 1][leftX + 1]) && isdigit(array[y + 1][leftX + 2]) && x != 0)
                        {
                            starArray[y][x]++;
                        }
                    }
                    else if (isdigit(array[y + 1][leftX + 1]))
                    {
                        starArray[y][x]++;
                    }
                    else if (x != 0 && isdigit(array[y + 1][leftX + 2]) && !isdigit(array[y + 1][leftX + 1]))
                    {
                        starArray[y][x]++;
                    }
                }

                //Policko vlevo
                if (x != 0)
                {
                    if (isdigit(array[y][x - 1]))
                    {
                        starArray[y][x]++;
                    }
                }

                //Policko vpravo
                if (x <= 141)
                {
                    if(isdigit(array[y][x + 1]))
                    {
                        starArray[y][x]++;
                    }
                }
                
            }
        }
    }

    for (y = 0; y <= LAST_LINE; y++)
    {
        for (int x = 0; array[y][x] != '\0'; x++)
        {
            if (starArray[y][x] == 3)
            {
                int num1 = -1;
                int num2 = -1;

                char charNum[10];
                memset(charNum, '0', 10);

                int pseudoX = x - 2;

                //vlevo
                if(isdigit(array[y][x - 1]))
                {
                    int charNumPos = 9;
                    charNum[charNumPos--] = array[y][x - 1];
                    while (isdigit(array[y][pseudoX]))
                    {
                        charNum[charNumPos--] = array[y][pseudoX];
                        pseudoX--;
                    }
                    while (charNumPos >= 0)
                    {
                        charNum[charNumPos--] = '0';
                    }

                    if (num1 == -1)
                    {
                        num1 = atoi(charNum);
                    }
                    else
                    {
                        num2 = atoi(charNum);
                    }
                    memset(charNum, '0', 10);
                }
                pseudoX = x + 2;

                //vpravo
                if(isdigit(array[y][x + 1]))
                {
                    int charNumPos = 0;
                    charNum[charNumPos++] = array[y][x + 1];

                    while (isdigit(array[y][pseudoX]))
                    {
                        charNum[charNumPos++] = array[y][pseudoX];
                        pseudoX++;
                    }
                    charNum[charNumPos] = '\0';

                    if (num1 == -1)
                    {
                        num1 = atoi(charNum);
                    }
                    else
                    {
                        num2 = atoi(charNum);
                    }
                    memset(charNum, '0', 10);
                }

                //NAHORE
                if (y != 0)
                {
                    //Pokud je prostredni necislo, muzou se na tom radku nachazet obe cisla
                    if (!isdigit(array[y - 1][x]))
                    {
                        //Pokud je cislo na x-1 -> pujdu doleva a budu ukladat zprava doleva
                        if (isdigit(array[y - 1][x - 1]))
                        {
                            int charNumPos = 9;
                            charNum[charNumPos--] = array[y - 1][x - 1];

                            int pseudoX = x - 2;
                            while (isdigit(array[y - 1][pseudoX]))
                            {
                                charNum[charNumPos--] = array[y - 1][pseudoX];
                                pseudoX--;
                            }

                            if (num1 == -1)
                            {
                                num1 = atoi(charNum);
                            }
                            else
                            {
                                num2 = atoi(charNum);
                            }
                            memset(charNum, '0', 10);
                        }

                        //Pokud je cislo na x+1 ->  pujdu doprava a budu ukladat zleva doprava
                        if (isdigit(array[y - 1][x + 1]))
                        {
                            int charNumPos = 0;
                            charNum[charNumPos++] = array[y - 1][x + 1];

                            int pseudoX = x + 2;
                            while (isdigit(array[y - 1][pseudoX]))
                            {
                                charNum[charNumPos++] = array[y - 1][pseudoX];
                                pseudoX++;
                            }
                            charNum[charNumPos] = '\0';

                            if (num1 == -1)
                            {
                                num1 = atoi(charNum);
                            }
                            else
                            {
                                num2 = atoi(charNum);
                            }
                            memset(charNum, '0', 10);
                        }
                    }
                    else
                    {
                        //Prostredni je cislo -> max jedno cislo v tomto radku
                        //Ulozim si ho doprostred charNum a pujdu doprava i doleva
                        charNum[5] = array[y - 1][x];
                        int pos = 1;
                        while (isdigit(array[y - 1][x - pos]))
                        {
                            charNum[5 - pos] = array[y - 1][x - pos];
                            pos++;
                        }
                        pos = 1;
                        while (isdigit(array[y - 1][x + pos]))
                        {
                            charNum[5 + pos] = array[y - 1][x + pos];
                            pos++;
                        }
                        charNum[5 + pos] = '\0';

                        if (num1 == -1)
                        {
                            num1 = atoi(charNum);
                        }
                        else
                        {
                            num2 = atoi(charNum);
                        }
                        memset(charNum, '0', 10);
                    }
                }

                //DOLE
                if (y != LAST_LINE)
                {
                    //Pokud je prostredni necislo, muzou se na tom radku nachazet obe cisla
                    if (!isdigit(array[y + 1][x]))
                    {
                        //Pokud je cislo na x-1 -> pujdu doleva a budu ukladat zprava doleva
                        if (isdigit(array[y + 1][x - 1]))
                        {
                            int charNumPos = 9;
                            charNum[charNumPos--] = array[y + 1][x - 1];

                            int pseudoX = x - 2;
                            while (isdigit(array[y + 1][pseudoX]))
                            {
                                charNum[charNumPos--] = array[y + 1][pseudoX];
                                pseudoX--;
                            }

                            if (num1 == -1)
                            {
                                num1 = atoi(charNum);
                            }
                            else
                            {
                                num2 = atoi(charNum);
                            }
                            memset(charNum, '0', 10);
                        }

                        //Pokud je cislo na x+1 ->  pujdu doprava a budu ukladat zleva doprava
                        if (isdigit(array[y + 1][x + 1]))
                        {
                            int charNumPos = 0;
                            charNum[charNumPos++] = array[y + 1][x + 1];

                            int pseudoX = x + 2;
                            while (isdigit(array[y + 1][pseudoX]))
                            {
                                charNum[charNumPos++] = array[y + 1][pseudoX];
                                pseudoX++;
                            }
                            charNum[charNumPos] = '\0';

                            if (num1 == -1)
                            {
                                num1 = atoi(charNum);
                            }
                            else
                            {
                                num2 = atoi(charNum);
                            }
                            memset(charNum, '0', 10);
                        }
                    }
                    else
                    {
                        //Prostredni je cislo -> max jedno cislo v tomto radku
                        //Ulozim si ho doprostred charNum a pujdu doprava i doleva
                        charNum[5] = array[y + 1][x];
                        int pos = 1;
                        while (isdigit(array[y + 1][x - pos]))
                        {
                            charNum[5 - pos] = array[y + 1][x - pos];
                            pos++;
                        }

                        pos = 1;
                        while (isdigit(array[y + 1][x + pos]))
                        {
                            charNum[5 + pos] = array[y + 1][x + pos];
                            pos++;
                        }
                        charNum[5 + pos] = '\0';

                        if (num1 == -1)
                        {
                            num1 = atoi(charNum);
                        }
                        else
                        {
                            num2 = atoi(charNum);
                        }
                        memset(charNum, '0', 10);
                    }
                }

                result += num1*num2;
            }
        }
    }

    printf("%d\n", result);

    for (int i = 0; i < 150; i++)
    {
        free(array[i]);
    }

    fclose(fp);
    return 0;
}