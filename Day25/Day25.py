with open("input.txt", 'r') as file:
    data = file.read().splitlines()
    e, moved, maxx, maxy = 0, True, len(data[0]), len(data)
    grid = {(x,y) : data[y][x] for x in range(maxx) for y in range(maxy)}
    while moved:
        moved = set()
        for x,y in [(x,y) for x,y in grid if grid[x,y] == '>' and grid[(x + 1) % maxx, y] == '.']:
            grid[(x + 1) % maxx, y] = grid[x,y]
            grid[x,y] = '.' 
            moved.add((x,y))
        for x,y in [(x,y) for x,y in grid if grid[x,y] == 'v' and grid[x, (y + 1) % maxy] == '.']:
            grid[x, (y + 1) % maxy] = grid[x,y]
            grid[x,y] = '.'
            moved.add((x,y))
        e += 1
    print(e) # 520

'''
     *
    /.\
   /..'\
   /'.'\
  /.''.'\
  /.'.'.\
 /'.''.'.\
 ^^^[_]^^^
  __  __                             _____  _            _       _                            _  _ 
 |  \/  |                           / ____|| |          (_)     | |                          | || |
 | \  / |  ___  _ __  _ __  _   _  | |     | |__   _ __  _  ___ | |_  _ __ ___    __ _  ___  | || |
 | |\/| | / _ \| '__|| '__|| | | | | |     | '_ \ | '__|| |/ __|| __|| '_ ` _ \  / _` |/ __| | || |
 | |  | ||  __/| |   | |   | |_| | | |____ | | | || |   | |\__ \| |_ | | | | | || (_| |\__ \ |_||_|
 |_|  |_| \___||_|   |_|    \__, |  \_____||_| |_||_|   |_||___/ \__||_| |_| |_| \__,_||___/ (_)(_)
                             __/ |                                                                 
                            |___/       
'''