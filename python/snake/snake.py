import random, sys, time, keyboard, os, playsound
from playsound import playsound

os.system('mode con: cols=100 lines=21')
snakebody = chr(9633)
foodchar = chr(9733)
height = 21
width = 101

snake = []
field = {}

class food:
    def __init__(self, position):
        Same = True
        while Same:
            Newposition = (random.randint(1,width-3),random.randint(1,height-3))
            for i in range (len(snake)):
                if Newposition == snake[i].position:
                     break
            else:
                Same = False
        self.position = Newposition
        field[self.position] = foodchar

class snakepart:
    def __init__(self, position, direction):
        self.position = position
        self.direction = direction
    def addDirection(self, multiply):
        x,y = multiply*self.direction[0]+self.position[0],multiply*self.direction[1]+self.position[1]
        return (x,y)


for x in range(width-1):
    for y in range(height-1):
        if x == 0 or y == 0 or x == width-2 or y == height-2:
            field[(x,y)] = 'a'
        else: 
            field[(x,y)] = ' '

start = (random.randint(0,width-3),random.randint(0,height-3))
foodstart = (random.randint(0,width-3),random.randint(0,height-3))
while start == foodstart: foodstart = (random.randint(0,width-3),random.randint(0,height-3))

if (width - start[0]) >= start[0]:
    startdirection = (1,0)
else: 
    startdirection = (-1,0)

head = snakepart(start, startdirection)
snake.append(head)

newfood = food(foodstart)
field[start] = snakebody

counter = 0
score = 0
tempdirection = startdirection

while True:
    if keyboard.is_pressed('w') and snake[0].direction != (0,1):
        tempdirection = (0,-1)
    elif keyboard.is_pressed('a') and snake[0].direction != (1,0):
        tempdirection = (-1,0)
    elif keyboard.is_pressed('s') and snake[0].direction != (0,-1):
        tempdirection = (0,1)
    elif keyboard.is_pressed('d') and snake[0].direction != (-1,0):
        tempdirection = (1,0)
        
    if counter % 4 == 0:
        print('\n' * 50)
        #Every snake segment will copy the direction of the segment before it with a one frame delay
        for i in range(1,len(snake)):
            snake[-i].direction = snake[-(i+1)].direction
            field[snake[-i].position] = ' '
            snake[-i].position = snake[-i].addDirection(1)
        field[snake[0].position] = ' '
        snake[0].direction = tempdirection
        snake[0].position = snake[0].addDirection(1)

        for i in range (len(snake)):
            field[snake[i].position] = snakebody

        if snake[0].position == newfood.position:
            newPart = snakepart((snake[-1].addDirection(-1)),snake[-1].direction)
            snake.append(newPart)
            newfood = food(newfood.position)
            playsound('smw_power-up.wav', False)
            score += 1

        field[newfood.position] = foodchar

        if snake[0].position[0] == 0 or snake[0].position[0] == width-2 or snake[0].position[1] == height-2 or snake[0].position[1] == 0:
            print('Game Over')
            input('Press any key...')
            sys.exit()
            
        for i in  range (1, len(snake)):
            if snake[0].position == snake[i].position:
                print('Game Over')
                input('Press any key...')
                sys.exit()

        for y in range(height-1):
            for x in range(width-1):
                print(field[x,y], end= '')
        print()
    if counter % 4980 == 0:
        playsound('Tetris.mp3', False)
    counter += 1
    try:
       time.sleep((1/60))
    except KeyboardInterrupt:
        print("Snake")
        sys.exit()