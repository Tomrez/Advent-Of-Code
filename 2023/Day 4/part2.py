import sys
import re
import numpy as np

def main():
    
    result = 0

    ticketsArray = np.ones(208, dtype=int)

    lineCounter = 0

    with open('part1.in', 'r') as file:
        for line in file:
            points = 0

            lineWithoutGameNum = line.split(':')[1]
            winNums = ((lineWithoutGameNum.split('|')[0]).strip()).split(' ')
            winNums = list(filter(None, winNums))
            gameNums = ((lineWithoutGameNum.split('|')[1]).strip()).split(' ')
            winNums = list(filter(None, winNums))

            for  i in range(ticketsArray[lineCounter]):
                for num in gameNums:
                    if num in winNums:
                        points += 1

                for j in range(points):
                    if ((lineCounter + j + 1) < 208):
                        ticketsArray[lineCounter + j + 1] += 1

                points = 0

            lineCounter += 1

        result = sum(ticketsArray)
        print(result)

if __name__ == "__main__":
    main()