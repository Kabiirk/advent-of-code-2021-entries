sub_system  = []
with open('input10.txt', 'r') as f:
    for line in f:
        sub_system.append( line.strip() )

print(sub_system)

closing_chunk = {
    '(' : ')',
    '[' : ']',
    '{' : '}',
    '<' : '>',
}

score = {
    ')' : 3,
    ']' : 57,
    '}' : 1197,
    '>' : 25137
}