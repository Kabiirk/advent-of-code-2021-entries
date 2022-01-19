from collections import Counter # for Part 2

with open('input.txt', 'r') as f:
    for line in f:
        starting_fish = line.strip().split(',')

starting_fish = [ int(fish) for fish in starting_fish ]

# Same Function is used for both parts
def grow( fishes, max_days ):
    for i in range(max_days):
        fishes.append(fishes.pop(0))
        fishes[6] += fishes[-1]
    return sum(fishes)


# Part 1
c1 = Counter(starting_fish)
data = [c1[i] for i in range(9)]
print(c1)
print(data)
print(grow(data, 80)) # 343441

# Part 2
c2 = Counter(starting_fish)
data = [c2[i] for i in range(9)]
print(c2)
print(data)
print(grow(data, 256)) # 1569108373832