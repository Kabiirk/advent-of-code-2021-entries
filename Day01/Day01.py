depths = []

with open('input.txt', 'r') as f:
    for line in f:
        depths.append(int(line.strip()))

n = len(depths)
depth_increase = 0

# Part 1
for i in range(1, n):
    if(depths[i] > depths[i-1]):
        depth_increase+=1

print(depth_increase) # 1502

# Part 2
# current window - previous window = (x3 + x2 + x1) - (x2 + x1 + x0) = x3 - x0
window_increase = 0
for i in range(3, n):
    if(depths[i] > depths[i-3]):
        window_increase+=1

print(window_increase) # 1538