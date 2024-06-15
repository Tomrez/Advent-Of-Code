#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define T 10
#define J 11
#define Q 12
#define K 13
#define A 14

#define FIVE 110
#define FOUR 109
#define FULLH 108
#define THREE 107
#define TWOP 106
#define ONEP 105
#define HIGHESTC 104

#define INPUT_COUNT 1000


bool isFiveOfKind(char *hand)
{
    char c = hand[0];

    for (int i = 1; i < 5; i++)
    {
        if (hand[i] != c)
        {
            return false;
        }
    }
    return true;
}

bool isFourOfKind(char *hand)
{
    int array[256];
    memset(array, 0, 256*sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        array[hand[i]] += 1;
    }

    for (int i = 0; i < 255; i++)
    {
        if (array[i] == 4)
        {
            return true;
        }
    }
    return false;
}

bool isFullHouse(char *hand)
{
    int array[256];
    memset(array, 0, 256*sizeof(int));

    bool three = false;
    bool two = false;

    for (int i = 0; i < 5; i++)
    {
        array[hand[i]] += 1;
    }

    for (int i = 0; i < 255; i++)
    {
        if (array[i] == 3)
        {
            three = true;
        }
        else if(array[i] == 2)
        {
            two = true;
        }
    }
    return three && two;
}

bool isThreeOfKind(char *hand)
{
    int array[256];
    memset(array, 0, 256*sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        array[hand[i]] += 1;
    }

    for (int i = 0; i < 255; i++)
    {
        if (array[i] == 3)
        {
            return true;
        }
    }
    return false;
}

bool isTwoPairs(char *hand)
{
    int array[256];
    memset(array, 0, 256*sizeof(int));

    bool pair1 = false;
    bool pair2 = false;

    for (int i = 0; i < 5; i++)
    {
        array[hand[i]] += 1;
    }

    for (int i = 0; i < 255; i++)
    {
        if (array[i] == 2 && pair1 == false)
        {
            pair1 = true;
        }
        else if(array[i] == 2)
        {
            pair2 = true;
        }
    }

    return pair1 && pair2;
}

bool isOnePair(char *hand)
{
    int array[256];
    memset(array, 0, 256*sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        array[hand[i]] += 1;
    }

    for (int i = 0; i < 255; i++)
    {
        if (array[i] == 2)
        {
            return true;
        }
    }
    return false;
}

int handType(char *hand)
{
    if (isFiveOfKind(hand))
        return FIVE;
    else if (isFourOfKind(hand))
        return FOUR;
    else if (isFullHouse(hand))
        return FULLH;
    else if (isThreeOfKind(hand))
        return THREE;
    else if (isTwoPairs(hand))
        return TWOP;
    else if (isOnePair(hand))
        return ONEP;
    else if (*hand == '\0')
        return -1;
    else
        return HIGHESTC;
}

void swap(char **handsArray, int *bidsArray, int firstPos, int secondPos)
{
    char *handTmp = handsArray[firstPos];
    int bidTmp = bidsArray[firstPos];

    handsArray[firstPos] = handsArray[secondPos];
    bidsArray[firstPos] = bidsArray[secondPos];

    handsArray[secondPos] = handTmp;
    bidsArray[secondPos] = bidTmp;
}

int cardToNumber(char c)
{
    if (isdigit(c))
    {
        return c - '0';
    }
    else
    {
        switch(c)
        {
            case 'K':
                return K;
                break;
            case 'Q':
                return Q;
                break;
            case 'T':
                return T;
                break;
            case 'J':
                return J;
                break;
            case 'A':
                return A;
                break;
        }
        return -1;
    }
}

void sortHandType(char **handsArray, int *bidsArray, int startPos, int endPos)
{
    for (int j = startPos; j <= endPos - 1; j++)
    {
        for (int k = j + 1; k <= endPos; k++)
        {
            for (int m = 0; m < 5; m++)
            {
                if (handsArray[k][m] != handsArray[j][m])
                {
                    int num1 = cardToNumber(handsArray[k][m]);
                    int num2 = cardToNumber(handsArray[j][m]);

                    if (num2 < num1)
                    {
                        swap(handsArray, bidsArray, k, j);
                    }
                    break;
                }
            }
        }
    }
}

int main()
{
    FILE *fp = fopen("part1.in", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "File error");
        return 1;
    }

    long result = 0;

    char *handsArray[INPUT_COUNT + 1];
    handsArray[INPUT_COUNT] = '\0';

    int bidsArray[INPUT_COUNT];

    char buffer[512];
    memset(buffer, '\0', 512);

    int i = 0;
    //STORE INTO ARRAYS
    while(fgets(buffer, 512, fp) != NULL)
    {
        char *token = strtok(buffer, " ");

        handsArray[i] = malloc(sizeof(char)*strlen(token));
        strcpy(handsArray[i], token);
        bidsArray[i] = atoi(strtok(NULL, " "));

        i++;
        memset(buffer, '\0', 512);
    }

    //SORT ARRAYS WITH HAND TYPES
    for (int j = 0; j < INPUT_COUNT - 1; j++)
    {
        for (int k = j + 1; k < INPUT_COUNT; k++)
        {
            if (handType(handsArray[j]) < handType(handsArray[k]))
            {
                swap(handsArray, bidsArray, j, k);
            }
        }
    }

    int endPos = 0;
    //SORT HAND TYPES WITH STRENGTH
    while(endPos < INPUT_COUNT)
    {
        int startPos = endPos;
        while((endPos < (INPUT_COUNT - 1) && handType(handsArray[endPos]) == handType(handsArray[endPos + 1])))
        {
            endPos++;
        }
        sortHandType(handsArray, bidsArray, startPos, endPos);
        endPos++;
    }

    for (int z = 0; z < INPUT_COUNT; z++)
    {
        result += bidsArray[z] * (INPUT_COUNT - z);
    }

    printf("%ld\n", result);

    fclose(fp);
    return 0;
}