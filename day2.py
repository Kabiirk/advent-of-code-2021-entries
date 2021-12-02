coordinates = []
with open('input2.txt', 'r') as f:
    for line in f:
        current_coordinate = line.strip().split(' ') # [ Instruction, value ]
        if(current_coordinate[0] == 'up'):
            current_coordinate[1] = -int(current_coordinate[1])
        else:
            current_coordinate[1] = int(current_coordinate[1])
        coordinates.append(current_coordinate)

#print(coordinates)

# Part 1
final_coordinates = {
                    'horizontal' : 0, 
                    'depth' : 0
                    }

for coordinate in coordinates:
    if(coordinate[0] == 'forward'):
        final_coordinates['horizontal'] += coordinate[1]
    if( (coordinate[0] == 'up') or (coordinate[0] == 'down') ):
        final_coordinates['depth'] += coordinate[1]

print(final_coordinates) # {'horizontal': 1965, 'depth': 1182}
print(final_coordinates['depth'] * final_coordinates['horizontal']) # 2322630

# Part 2
final_coordinates_aim = {
                        'horizontal' : 0, 
                        'depth' : 0,
                        'aim' : 0
                        }

for coordinate in coordinates:
    if(coordinate[0] == 'forward'):
        final_coordinates_aim['horizontal'] += coordinate[1]
        final_coordinates_aim['depth'] += final_coordinates_aim['aim'] * coordinate[1]
    if( (coordinate[0] == 'up') or (coordinate[0] == 'down') ):
        final_coordinates_aim['aim'] += coordinate[1]
    # print(coordinate, " : " , final_coordinates_aim)

print(final_coordinates_aim) # {'horizontal': 1965, 'depth': 1071386, 'aim': 1182}
print(final_coordinates_aim['depth'] * final_coordinates_aim['horizontal']) # 2105273490