vent_lines = []
with open('input5.txt', 'r') as f:
    for line in f:
        current_entry = line.strip().split(' -> ')
        x1, y1 = map(int, current_entry[0].split(','))
        x2, y2 = map(int, current_entry[1].split(','))
        vent_lines.append([x1, y1, x2, y2])

#print(vent_lines)


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
        for i in range(x1, x2+1):
            field[i][y1]+=1
    elif(x1 == x2):
        # Same x coord (x1 == x2)
        #print("Verti !", line)
        for j in range(y1, y2+1):
            field[x1][j]+=1
    else:
        pass

# Assume 1000 x 1000 map
field = []
size = 1000
for i in range(size):
    row = []
    for j in range(size):
        row.append(0)
    field.append(row)

for line in vent_lines:
    draw_line(field, line)

# field[0][0]+=1
# field[0][1]+=1
# field[1][1]+=1
# field[1][0]+=1

# for row in field:
#     print(row)
#     print('\r')
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

    if(y1 == y2):
        # Same y coord (y1 == y2)
        #print("Hori !", line)
        for i in range(x1, x2+1):
            field[i][y1]+=1
    elif(x1 == x2):
        # Same x coord (x1 == x2)
        #print("Verti !", line)
        for j in range(y1, y2+1):
            field[x1][j]+=1
    elif( y2-y1 == x2-x1 ):
        # Diagonal slope 45 Deg.
        for i in range(x1, x2+1):
            for j in range(y1, y2+1):
                field[i][j]+=1
    else:
        pass

# Assume 1000 x 1000 map
field = []
size = 1000
for i in range(size):
    row = []
    for j in range(size):
        row.append(0)
    field.append(row)

for line in vent_lines:
    draw_line_diag(field, line)
count_intersection = 0
for row in field:
    for col in row:
        if(col >= 2):
            count_intersection += 1
print(count_intersection) # 19676