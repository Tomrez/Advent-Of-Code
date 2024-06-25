import sys
import re

def main():
    with open ('./input.in', 'r') as file:
        while True:
            lines = []
            for _ in range(3):
                line = file.readline()
                if not line:
                    break
                lines.append(line.strip())

            print(lines)



if __name__ == "__main__":
    main()