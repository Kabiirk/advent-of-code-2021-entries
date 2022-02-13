dots  = set()
instructions = []
with open('input.txt', 'r') as f:
    for line in f:
        if(line.split(' ')[0] == 'fold'):
            axis = line.split('=')[0][-1]
            value = line.split('=')[1]
            instructions.append( [axis, int(value)] )
        elif(line == '\n'):
            # To skip the newline between coordinates and instructions
            continue
        else:
            temp = line.strip().split(',')
            x = int(temp[0])
            y = int(temp[1])
            dots.add( (x,y) )

# Common Funtion
def fold(coord_set, fold):
    axis, fold_value = fold
    new_dot_set = set()
    
    for this_coord in coord_set:
        x, y = this_coord
        if axis == 'x':
            # Vertical folding action 
            # If x is bigger than the fold, it's value will change
            # The formula for how it will change is 2 * fold_value - x
            
            # If x is smaller, no change, but add to new set
            # because of inward folding
            if x > fold_value:
                new_dot_set.add((2 * fold_value - x, y))
            else:
                new_dot_set.add((x, y))
        else: 
            # axis == 'y' i.e. Horizontal folding action
            # Same as above, but for y now.
            if y > fold_value:
                new_dot_set.add((x, 2 * fold_value - y))
            else:
                new_dot_set.add((x, y))

    return new_dot_set

# Part 1
first_fold = fold(dots, instructions[0])
print(len(first_fold)) # 763

# Part 2
for instruction in instructions:
    dots = fold(dots, instruction)

# Print output as Pattern
max_x = 0
max_y = 0

for dot in dots:
    x,y = dot
    if(x > max_x):
        max_x = x
    if(y > max_y):
        max_y = y

# Display output by 'drawing' final folded sheet
for y in range(max_y+1):
    output = ''
    for x in range(max_x+1):
        if (x,y) in dots:
            output += '#'
        else:
            output+=' '
    print(output)

# Part 2 Answer = RHALRCRA
# Output :
#   ###  #  #  ##  #    ###   ##  ###   ## 
#   #  # #  # #  # #    #  # #  # #  # #  #
#   #  # #### #  # #    #  # #    #  # #  #
#   ###  #  # #### #    ###  #    ###  ####
#   # #  #  # #  # #    # #  #  # # #  #  #
#   #  # #  # #  # #### #  #  ##  #  # #  #