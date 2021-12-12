caves  = []
with open('input12.txt', 'r') as f:
    for line in f:
        caves.append( line.strip().split('-') )

# print(caves)

# Basic DFS
graph = {}
for v in caves: 
    for i in range(2): 
        graph.setdefault(v[i], []).append(v[i - 1])
n_visits = {node: 0 for node in graph}

def search(stack, node, n_paths, doubles_allowed):
    if n_visits[node] and node.islower():
        if not doubles_allowed or node == "start":
            return n_paths
        doubles_allowed = False
    if node == 'end':
        return n_paths + 1
    else:
        stack.append(node)
        n_visits[node] += 1
        for nb in graph[node]:
            n_paths = search(stack, nb, n_paths, doubles_allowed)
        stack.pop()
        n_visits[node] -= 1
        if n_visits[node] and node.islower():
            doubles_allowed = True
    return n_paths

# Part 1
print(search([], 'start', 0, False)) # 3298

# Part 2
print(search([], 'start', 0, True)) # 93572