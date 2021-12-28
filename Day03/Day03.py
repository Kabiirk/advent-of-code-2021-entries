diagnostic_report = []
with open('input.txt', 'r') as f:
    for line in f:
        current_entry = line.strip() # 111100101100
        diagnostic_report.append(current_entry)
    
# print(diagnostic_report)
# print(len(diagnostic_report))

# Debugging
# diagnostic_report = [
#     '00100',
#     '11110',
#     '10110',
#     '10111',
#     '10101',
#     '01111',
#     '00111',
#     '11100',
#     '10000',
#     '11001',
#     '00010',
#     '01010'
# ]

# Part 1
def most_common_bit( array_of_bit_strings, position_to_check, *args ):
    set_bit_count = 0
    unset_bit_count = 0
    for bit_string in array_of_bit_strings:
        if(bit_string[position_to_check] == '1'):
            set_bit_count += 1
        if(bit_string[position_to_check] == '0'):
            unset_bit_count += 1

    if(set_bit_count == unset_bit_count):
        return '1'

    return str(int(set_bit_count > unset_bit_count))

gamma_rate_string = ''
n = len(diagnostic_report[0])
for i in range(n):
    gamma_rate_string += most_common_bit(diagnostic_report, i)
gamma_rate = int(gamma_rate_string, 2)

# inverting to get epsilon rate
epsilon_rate_string = ''.join('1' if x == '0' else '0' for x in gamma_rate_string)
epsilon_rate = int(epsilon_rate_string, 2)

print(gamma_rate * epsilon_rate) # 845186

# Part 2
# gamma_rate_string = most common bits
# epsilon_rate_string = least common bits
def least_common_bit( array_of_bit_strings, position_to_check, *args ):
    set_bit_count = 0
    unset_bit_count = 0
    for bit_string in array_of_bit_strings:
        if(bit_string[position_to_check] == '1'):
            set_bit_count += 1
        if(bit_string[position_to_check] == '0'):
            unset_bit_count += 1

    if(set_bit_count == unset_bit_count):
        return '0'

    return str(int(set_bit_count < unset_bit_count))

def recursive_search(array, index, mode):
    if len(array) == 1:
        return array[0]
    else:
        if mode == 'most':
            current_column = most_common_bit(array, index)
        elif mode == 'least':
            current_column = least_common_bit(array, index)
        new_array = []
        for item in array:
            if item[index] == current_column:
                new_array.append(item)
        index += 1
        return recursive_search(new_array, index, mode)

o2_gen_rating_string = recursive_search(diagnostic_report, 0, 'most') # 010110110011
co2_scrub_rating_string = recursive_search(diagnostic_report, 0, 'least') # 110001101010


o2_gen_rating = int(o2_gen_rating_string, 2)
co2_scrub_rating = int(co2_scrub_rating_string, 2)
print(o2_gen_rating*co2_scrub_rating) # 4636702