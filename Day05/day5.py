vent_lines = []
with open('input.txt', 'r') as f:
    for line in f:
        current_entry = line.strip().split(' -> ')
        x1, y1 = map(int, current_entry[0].split(','))
        x2, y2 = map(int, current_entry[1].split(','))
        vent_lines.append([x1, y1, x2, y2])

#print(vent_lines)
max_size = 0
for line in vent_lines:
    for col in line:
        if(col>max_size):
            max_size = col

#print(max_size)

# Part 1
def draw_line(field, line):
    '''
    Draws Vent line on the field by incrementing entry at x,y posn.

    field : 2D Array reprsenting 2D field surface
    line : [x1, y1, x2, y2]start and end point of Vent Line
    '''
    x1 = line[0]
    y1 = line[1]
    x2 = line[2]
    y2 = line[3]

    if(y1 == y2):
        # Same y coord (y1 == y2)
        #print("Hori !", line)
        for i in range(min(x1, x2), max(x1,x2)+1):
            field[y1][i]+=1
    elif(x1 == x2):
        # Same x coord (x1 == x2)
        #print("Verti !", line)
        for j in range(min(y1, y2), max(y1, y2)+1):
            field[j][x1]+=1


field = [[0 for i in range(max_size + 1)] for j in range(max_size + 1)]

for line in vent_lines:
    draw_line(field, line)

count_intersection = 0
for row in field:
    for col in row:
        if(col >= 2):
            count_intersection += 1

print(count_intersection) # 7414


# Part 2
def draw_line_diag(field, line):
    '''
    Draws Vent line on the field by incrementing entry at x,y posn.

    field : 2D Array reprsenting 2D field surface
    line : [x1, y1, x2, y2]start and end point of Vent Line
    '''
    x1 = line[0]
    y1 = line[1]
    x2 = line[2]
    y2 = line[3]
    slopey =  ( max(y1,y2) - min(y1, y2) )
    slopex =  ( max(x1,x2) - min(x1, x2) )

    if(y1 == y2):
        # Same y coord (y1 == y2)
        #print("Hori !", line)
        for i in range(min(x1, x2), max(x1,x2)+1):
            field[y1][i]+=1
    elif(x1 == x2):
        # Same x coord (x1 == x2)
        #print("Verti !", line)
        for j in range(min(y1, y2), max(y1,y2)+1):
            field[j][x1]+=1
    else:
        xs, x, ys, y = min(x1, x2),\
                       max(x1, x2), \
                       [y1, y2][x1 > x2],\
                       [y1, y2][x1 < x2]

        y_new = ys
        for i in range(xs, x+1):
            field[y_new][i] += 1
            y_new += [-1, 1][ys < y]


field = [[0 for i in range(max_size + 1)] for j in range(max_size + 1)]

for line in vent_lines:
    draw_line_diag(field, line)

count_intersection = 0
for row in field:
    for col in row:
        if(col >= 2):
            count_intersection += 1
print(count_intersection) # 19676