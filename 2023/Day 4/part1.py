import sys
import re

def main():
    
    result = 0

    with open('part1.in', 'r') as file:
        for line in file:
            points = 0

            lineWithoutGameNum = line.split(':')[1]
            winNums = ((lineWithoutGameNum.split('|')[0]).strip()).split(' ')
            winNums = list(filter(None, winNums))
            gameNums = ((lineWithoutGameNum.split('|')[1]).strip()).split(' ')
            winNums = list(filter(None, winNums))

            for num in gameNums:
                if num in winNums:
                    if points == 0:
                        points = 1
                    else:
                        points = points * 2

            result += points
        print(result)

if __name__ == "__main__":
    main()