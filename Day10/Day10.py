from collections import deque

sub_system  = []
with open('input.txt', 'r') as f:
    for line in f:
        # because strings re immutable in python
        # line =  line.replace('{', 'a')
        # line = line.replace('}', 'b')
        sub_system.append( line.strip() )

pairs = {"(": ")", "[": "]", "{": "}", "<": ">"}
points = {")": 3, "]": 57, "}": 1197, ">": 25137}
part1, part2 = 0, []

for line in sub_system:
    stack = deque()
    for c in line.strip():
        if c in "([{<":
            stack.appendleft(pairs[c])
        elif c != stack.popleft():
            part1 += points[c]
            break
    else:
        score = 0
        for c in stack:
            score = score * 5 + ")]}>".index(c) + 1
        part2.append(score)

# Part 1
print(part1) # 387363

# Part 2
print(sorted(part2)[len(part2) // 2]) # 4330777059