real_input = open("input.txt").read().splitlines()
grid = {(m, n): int(c) for m, line in enumerate(real_input) for n, c in enumerate(line)}

def inc_neighbours(grid, m, n):
    neighbour_incs = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
    for dm, dn in neighbour_incs:
        if (m+dm, n+dn) in grid:
            grid[(m+dm, n+dn)] += 1

def flash(grid, already_flashed):
    next_grid = grid.copy()
    while True:
        flashed_now = set()
        for ind, v in grid.items():
            if v > 9 and ind not in already_flashed:
                flashed_now.add(ind)
                inc_neighbours(next_grid, *ind)
        if not flashed_now:
            break
        grid = next_grid
        already_flashed |= flashed_now
        yield already_flashed, next_grid

def step(grid):
    already_flashed = set()
    for ind in grid: grid[ind] += 1
    for already_flashed, grid in flash(grid, already_flashed): pass
    for ind in already_flashed: grid[ind] = 0
    return len(already_flashed), grid

total = 0
for i in range(1000):
    flashes, grid = step(grid)
    total += flashes
    if i == 99:
        # Part 1
        print(total) # 1739
    if flashes == len(grid):
        print(i+1) # 324
        break