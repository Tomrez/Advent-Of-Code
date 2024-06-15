import sys
import re

def main():

    result = 0

    with open('part1.in', 'r') as file:
        for line in file:

            redMin = 0
            blueMin = 0
            greenMin = 0

            gameInfo = line.split(':')
            games = gameInfo[1].split(';')

            for game in games:
                game = game.strip()
                gameColors = game.split(',')
                for gameColor in gameColors:
                    gameColor = gameColor.strip()
                    gameColorInfo = gameColor.split(' ')
                    print(gameColorInfo[0], gameColorInfo[1])
                    if gameColorInfo[1] == "green" and int(gameColorInfo[0]) > greenMin:
                        greenMin = int(gameColorInfo[0])
                    if gameColorInfo[1] == "red" and int(gameColorInfo[0]) > redMin:
                        redMin = int(gameColorInfo[0])
                    if gameColorInfo[1]== "blue" and int(gameColorInfo[0]) > blueMin:
                        blueMin = int(gameColorInfo[0])

            result = result + redMin*greenMin*blueMin
        print(result)
    sys.exit(0)


if __name__ == "__main__":
    main()