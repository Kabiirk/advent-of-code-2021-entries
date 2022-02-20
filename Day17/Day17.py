import re

with open('input.txt', 'r') as f:
    for line in f:
        res = re.compile(r'target area: x=(-?\d*)..(-?\d*), y=(-?\d*)..(-?\d*)')
        mo = res.search(line)
        target_range = list(map(int, mo.groups()))

velocities = []

def check_velocity_valid(dx, dy, target):
    tminx = target[0]
    tmaxx = target[1]
    tminy = target[2]
    tmaxy = target[3]
 
    pos_x = 0;
    pos_y = 0
    while(pos_x<=tmaxx and pos_y >=tminy):
        pos_x = pos_x+dx
        pos_y = pos_y+dy
        dx = max(0, dx-1)
        dy = dy-1
        if( (tminx <= pos_x and pos_x <= tmaxx) and (tminy <= pos_y and pos_y <= tmaxy) ):
            return True

    return False

def highest_y(y):
    return (y+1) * y // 2;


for dx in range(1000):
    for dy in range(-999,1000):
        if( check_velocity_valid(dx, dy, target_range) ):
            velocities.append(dy)

# Part 1
print(highest_y(max(velocities)))# 5151

# Part 2
print(len(velocities))# 968