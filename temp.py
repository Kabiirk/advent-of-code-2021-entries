lines = []
while True:
    try:
        a, b, c, d = map(int, input().replace(",", " ").replace(" -> ", " ").split())
        lines.append([(a, b), (c, d)])
    except ValueError:
        break
x = 0
for line in lines:
    if max(line[0]) > x or max(line[1]) > x:
        x = [max(line[0]), max(line[1])][max(line[0]) < max(line[1])]

diagram = [[0 for i in range(x + 1)] for j in range(x + 1)]
for line in lines:
    if line[0][1] == line[1][1]:
        for i in range(min(line[0][0], line[1][0]), max(line[0][0], line[1][0])+1):
            diagram[line[0][1]][i] += 1
    elif line[0][0] == line[1][0]:
        for i in range(min(line[0][1], line[1][1]), max(line[0][1], line[1][1])+1):
            diagram[i][line[0][0]] += 1
count_bigger = 0
for line in diagram:
    #print(line)
    for num in line:
        count_bigger += [0, 1][num > 1]

print(count_bigger)

lines = []
while True:
    try:
        a, b, c, d = map(int, input().replace(",", " ").replace(" -> ", " ").split())
        lines.append([(a, b), (c, d)])
    except ValueError:
        break
x = 0
for line in lines:
    if max(line[0]) > x or max(line[1]) > x:
        x = [max(line[0]), max(line[1])][max(line[0]) < max(line[1])]

diagram = [[0 for i in range(x + 1)] for j in range(x + 1)]
for line in lines:
    if line[0][1] == line[1][1]:
        for i in range(min(line[0][0], line[1][0]), max(line[0][0], line[1][0]) + 1):
            diagram[line[0][1]][i] += 1
    elif line[0][0] == line[1][0]:
        for i in range(min(line[0][1], line[1][1]), max(line[0][1], line[1][1]) + 1):
            diagram[i][line[0][0]] += 1
    else:
        print(line)
        xs, x, ys, y = min(line[0][0], line[1][0]),\
                       max(line[0][0], line[1][0]), \
                       [line[0][1], line[1][1]][line[0][0] > line[1][0]],\
                       [line[0][1], line[1][1]][line[0][0] < line[1][0]]
        yp = ys
        for i in range(xs, x+1):
            diagram[yp][i] += 1
            yp += [-1, 1][ys < y]

count_bigger = 0
for line in diagram:
    for num in line:
        count_bigger += [0, 1][num > 1]

print(count_bigger)