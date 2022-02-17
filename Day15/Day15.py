import sys
from collections import deque

def least_path_cost(cave):
    n = len(cave)
    # sys.maxsize = 9223372036854775807
    # Larger than any regular int value to
    # be used in this problem
    cost = []
    for i in range(n):
        c = []
        for j in range(n):
            c.append(sys.maxsize)
        cost.append(c)

    cost[0][0] = 0

    pending = deque()
    pending.append([0,0])

    while(not len(pending)==0):
        row,col = pending[0]
        pending.popleft()

        if(row>0 and (cost[row][col]+cave[row-1][col]<cost[row-1][col])):
            cost[row-1][col] = cost[row][col] + cave[row-1][col];
            pending.append([row-1, col])

        if(row+1<len(cost) and (cost[row][col]+cave[row+1][col]<cost[row+1][col])):
            cost[row+1][col] = cost[row][col] + cave[row+1][col];
            pending.append([row+1, col])

        if(col>0 and (cost[row][col]+cave[row][col-1]<cost[row][col-1])):
            cost[row][col-1] = cost[row][col] + cave[row][col-1];
            pending.append([row, col-1])

        if(col+1<len(cost[row]) and (cost[row][col]+cave[row][col+1]<cost[row][col+1])):
            cost[row][col+1] = cost[row][col] + cave[row][col+1];
            pending.append([row, col+1])

    # return cost[len(cost)-1][len(cost[len(cost)-1])-1];
    return cost[-1][-1];

def expand_cave(cave):
    n = len(cave)*5
    m = len(cave)

    result = []
    for i in range(n):
        c = []
        for j in range(n):
            c.append(0)
        result.append(c)

    for i in range(len(result)):
        for j in range(len(result[i])):
            result[i][j] =( ( cave[i%m][j%m] + i//m + j//m - 1 ) %9 ) + 1;

    return result


cave = []
with open('input.txt', 'r') as f:
    for line in f:
        working_line = line.split('\n')[0]
        int_array  = list(map(int, working_line))
        cave.append(int_array);

# Part 1
print(least_path_cost(cave))# 619

expanded_cave = expand_cave(cave)

# Part 2
print(least_path_cost(expanded_cave))# 2922