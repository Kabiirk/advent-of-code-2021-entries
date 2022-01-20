import math # for using infinity

with open('input.txt', 'r') as f:
    for line in f:
        crab_positions = line.strip().split(',')

crab_positions = [ int(crab_position) for crab_position in crab_positions ]

# Only minor change in function required to solve part 2 as well
# so doing it in the same function
def least_fuel_alignment( positions, part_two ):
    least_fuel = math.inf
    for i in range(min(positions), max(positions)+1):
        current_fuel = 0
        for position in positions:
            difference = abs(i - position)

            # minor modification to solve Part 2
            if(part_two):
                # Σn = 1 + 2 + 3 + 4 + .... + n = n(n+1)/2
                current_fuel += int(difference*(difference+1)/2)
            else:
                # Solves Part 1
                current_fuel += difference
        
        if(current_fuel < least_fuel):
            least_fuel = current_fuel

    return least_fuel

# Part 1
least_fuel = least_fuel_alignment(crab_positions, False)
print(least_fuel) # 347449

# Part 2
least_fuel = least_fuel_alignment(crab_positions, True)
print(least_fuel) # 98039527