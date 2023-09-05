import sys, random, time, bext

x,y = bext.size()

x -= 1
numberOfLogos = 5
pauseAmount = 0.1

colors = ['red', 'green','yellow','cyan', 'white','blue','magenta']
logos = []

def main():
    bext.clear()
    for i in range(numberOfLogos):
        logos.append({'color' : random.choice(colors), 'direction': (random.choice([-1,1]), random.choice([-1,1])), 'x' : random.randint(0,x-4), 'y' : random.randint(0,y-4)})
        if logos[i]['x'] % 2 == 1:
            logos[i]['x'] -= 1

    while True:
        for logo in logos:
            
            bext.goto(logo['x'],logo['y'])
            print('   ', end='')

            if logo['x'] == 0 and logo['y'] == 0:
                logo['direction'] = (logo['direction'][0]* -1,logo['direction'][1]*-1)
                logo['color'] = random.choice(colors)
            elif logo['x'] == 0 and logo['y'] == y-1:
                logo['direction'] = (logo['direction'][0]* -1,logo['direction'][1]*-1)
                logo['color'] = random.choice(colors)
            elif logo['x'] == x-3 and logo['y'] == 0:
                logo['direction'] = (logo['direction'][0]* -1,logo['direction'][1]*-1)
                logo['color'] = random.choice(colors)
            elif logo['x'] == x-3 and logo['y'] == y-1:
                logo['direction'] = (logo['direction'][0]* -1,logo['direction'][1]*-1)
                logo['color'] = random.choice(colors)
            elif logo['x'] == 0:
                logo['direction'] = (logo['direction'][0]* -1,logo['direction'][1])
                logo['color'] = random.choice(colors)
            elif logo['x'] == x-3:
                logo['direction'] = (logo['direction'][0]* -1,logo['direction'][1])
                logo['color'] = random.choice(colors)
            elif logo['y'] == 0:
                logo['direction'] = (logo['direction'][0],logo['direction'][1]*-1)
                logo['color'] = random.choice(colors)
            elif logo['y'] == y-1:
                logo['direction'] = (logo['direction'][0],logo['direction'][1]*-1)
                logo['color'] = random.choice(colors)
            logo['x'] += logo['direction'][0]*2
            logo['y'] += logo['direction'][1]
        for logo in logos:
            bext.goto(logo['x'],logo['y'])
            bext.fg(logo['color'])
            print('DVD', end='')
        
        bext.goto(0,0)

        sys.stdout.flush()
        time.sleep(pauseAmount)

try:
    main()
except KeyboardInterrupt:
    bext.goto(0,0)
    bext.fg('magenta')
    print()
    print('Welcome back')
    sys.exit()
