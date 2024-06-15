import sys
import re

red = 12
green = 13
blue = 14

def main():

    result = 0

    with open('part1.in', 'r') as file:
        for line in file:

            possibleGame = True

            gameInfo = line.split(':')

            gameNumber = gameInfo[0].split(' ')[1]

            games = gameInfo[1].split(';')

            for game in games:
                game = game.strip()
                gameColors = game.split(',')
                for gameColor in gameColors:
                    gameColor = gameColor.strip()
                    gameColorInfo = gameColor.split(' ')
                    if gameColorInfo[1] == "green" and int(gameColorInfo[0]) > green:
                        possibleGame = False
                    if gameColorInfo[1] == "red" and int(gameColorInfo[0]) > red:
                        possibleGame = False
                    if gameColorInfo[1]== "blue" and int(gameColorInfo[0]) > blue:
                        possibleGame = False
            if possibleGame is True:
                result += int(gameNumber)
        print(result)
    sys.exit(0)


if __name__ == "__main__":
    main()