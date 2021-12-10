entries  = []
with open('input9.txt', 'r') as f:
    for line in f:
        entries.append( list(map(int, line.strip())) )

print(entries)