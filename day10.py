sub_system  = []
with open('input10.txt', 'r') as f:
    for line in f:
        # because strings re immutable in python
        # line =  line.replace('{', 'a')
        # line = line.replace('}', 'b')
        sub_system.append( line.strip() )

#print(sub_system)

closing_bracket = {
    '(' : ')',
    '[' : ']',
    'a' : 'b',
    '<' : '>',
}

score = {
    ')' : 3,
    ']' : 57,
    'b' : 1197,
    '>' : 25137
}

def first_illegal_character( code_line ):
    '''
    Using list as stack where :
    [a, b, c, d, e, f, g]
     ^                 ^
    Bottom            Top
    '''

    illegals = []
    opening_bracket = []
    n = len(code_line)
    for i in range(n):
        if(code_line[i] in ['(', '[', 'a', '<'] ):
            # Add to top
            opening_bracket.append(code_line[i])
        elif(code_line[i] == closing_bracket[opening_bracket[-1]]):
            # remove from top
            opening_bracket.pop()
    return opening_bracket

s = '{([(<{}[<>[]}>{[]{[(<()>'
s = '[[<[([]))<([[{}[[()]]]'
s = s.replace('{', 'a')
s = s.replace('}', 'b')
# print(s)
# print(first_illegal_character(s))

from collections import deque
import fileinput

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