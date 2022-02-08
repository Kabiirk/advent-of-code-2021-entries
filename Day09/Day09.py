entries  = []
with open('input.txt', 'r') as f:
    for line in f:
        entries.append( list(map(int, line.strip())) )

n = len(entries)
low_points = []
low_points_coord = []

# Part 1
def check_lowpoint( checklist ):
    final = True
    for check in checklist:
        final = final and check
    
    return final

for i in range(0, n):
    m = len(entries[i])
    for j in range(0, m):

        # Non-border entries
        if(0<i<n-1 and 0<j<m-1):
            top = entries[i][j] < entries[i-1][j]
            left = entries[i][j] < entries[i][j-1]
            bottom = entries[i][j] < entries[i+1][j]
            right = entries[i][j] < entries[i][j+1]
            if(check_lowpoint([top, left, bottom, right])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))

        # Corners
        if(i == 0 and j == 0):
            bottom = entries[i][j] < entries[i+1][j]
            right = entries[i][j] < entries[i][j+1]
            if(check_lowpoint([bottom, right])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))
        if(i == 0 and j == m-1):
            left = entries[i][j] < entries[i][j-1]
            bottom = entries[i][j] < entries[i+1][j]
            if(check_lowpoint([left, bottom])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))
        if(i == n-1 and j == 0):
            top = entries[i][j] < entries[i-1][j]
            right = entries[i][j] < entries[i][j+1]
            if(check_lowpoint([top, right])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))
        if(i == n-1 and j == m-1):
            top = entries[i][j] < entries[i-1][j]
            left = entries[i][j] < entries[i][j-1]
            if(check_lowpoint([top, left])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))

        # Top row excluding corners
        if(i == 0 and 0<j<m-1):
            left = entries[i][j] < entries[i][j-1]
            bottom = entries[i][j] < entries[i+1][j]
            right = entries[i][j] < entries[i][j+1]
            if(check_lowpoint([left, bottom, right])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))

        # bottom row excluding corners
        if(i == n-1 and 0<j<m-1):
            top = entries[i][j] < entries[i-1][j]
            left = entries[i][j] < entries[i][j-1]
            right = entries[i][j] < entries[i][j+1]
            if(check_lowpoint([top, left, right])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))

        # left column excluding corners
        if(0<i<n-1 and j == 0):
            top = entries[i][j] < entries[i-1][j]
            bottom = entries[i][j] < entries[i+1][j]
            right = entries[i][j] < entries[i][j+1]
            if(check_lowpoint([top, bottom, right])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))

        # right column excluding corners
        if(0<i<n-1 and j == m-1):
            top = entries[i][j] < entries[i-1][j]
            left = entries[i][j] < entries[i][j-1]
            bottom = entries[i][j] < entries[i+1][j]
            if(check_lowpoint([top, left, bottom])):
                low_points.append(entries[i][j])
                low_points_coord.append((i,j))

print(sum(low_points) + len(low_points))# 566


# Part 2
def compare_rek(r,c,basin):
    dr = [1,0,-1,0]
    dc = [0,1,0,-1]
    newpoints = set()
    for i in range(4):
        rr,cc = r+dr[i],c+dc[i]
        if (rr,cc) not in basin and rr>=0 and cc >= 0 and rr < height and cc < width and entries[rr][cc]<9:
                newpoints.add((rr,cc))
    basin = basin.union(newpoints)
    for np in newpoints:
        basin = basin.union(compare_rek(np[0],np[1],basin))
    return basin

basins = []
height = len(entries)
width = len(entries[0])
for r,c in low_points_coord:
    basins += [len(compare_rek(r,c,set({(r,c)})))]
prod = 1
for i in range(3):
    maximum = max(basins)
    basins.remove(maximum)
    #print(maximum)
    prod *=maximum
print(prod)# 891684