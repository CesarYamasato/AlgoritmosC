import copy,sys,random, time
from turtle import right

Y = 43
X = 167

alive = '0'
dead = '.'

nextCells = {}

for y in range (Y):
    for x in range (X):
        if (random.choice([0,1])) == 0:
            nextCells[(x,y)] = dead
        else:
            nextCells[(x,y)] = alive

while True:
    print ('\n' * 50)
    cells = copy.deepcopy(nextCells)

    for y in range (Y):
        for x in range (X):
            print (cells[x,y], end='')
        print()

    for y in range (Y):
        for x in range (X):
            neightbors = 0

            left = (x-1) % X
            rite = (x+1) % X
            up = (y+1) % Y
            down = (y-1) % Y

            if (cells[left, y]) == alive:
                neightbors += 1
            if (cells[rite,y]) == alive:
                neightbors += 1
            if (cells[x,down]) == alive:
                neightbors += 1
            if (cells[left,up]) == alive:
                neightbors += 1
            if (cells[rite,up]) == alive:
                neightbors += 1
            if (cells[left,down]) == alive:
                neightbors += 1
            if (cells[rite,down]) == alive:
                neightbors += 1
            
            if neightbors < 2 or neightbors > 3:
                nextCells[(x,y)] = dead
            elif neightbors == 3:
                nextCells[(x,y)] = alive
    try:
        time.sleep(0.5)
    except KeyboardInterrupt:
        print("GameOfLife")
        sys.exit()
            


