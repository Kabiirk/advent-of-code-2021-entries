diagnostic_report = []
with open('input3.txt', 'r') as f:
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

    # To handle part 2
    if(set_bit_count == unset_bit_count):
        return '1'
        # if(args[0] == 'O2'):
        #     return '1'
        # if(args[0] == 'CO2'):
        #     return '0'

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

    # To handle part 2
    if(set_bit_count == unset_bit_count):
        return '0'

    return str(int(set_bit_count < unset_bit_count))

def iterative_elimanation( rating_list, type_of_rating ):
    flip_bit = {
        '1':'0',
        '0':'1'
    }
    comparison_tracker = 1 # already compared with bit at 0th index while poppulating the list
    
    while(len(rating_list) > 1):
        bit_to_compare = most_common_bit(rating_list, comparison_tracker, type_of_rating)
        if(type_of_rating == 'CO2'):
            bit_to_compare = least_common_bit(rating_list, comparison_tracker, type_of_rating)
        
        print(bit_to_compare, comparison_tracker, rating_list)
        
        for rating in rating_list:
            if(rating[comparison_tracker] != bit_to_compare):
                rating_list.remove(rating)
        comparison_tracker+=1
    return rating_list

# initial poppulation
o2_generator_rating_list = []
report_length = len(diagnostic_report)
for entry in diagnostic_report:
    if(entry[0] == most_common_bit(diagnostic_report, 0)):
        o2_generator_rating_list.append(entry)

co2_scrubber_rating_list = []
compare_bit = least_common_bit(diagnostic_report, 0)
for entry in diagnostic_report:
    if(entry[0] == compare_bit):
        co2_scrubber_rating_list.append(entry)

#print(co2_scrubber_rating_list)

o2_gen_rating_string =iterative_elimanation(o2_generator_rating_list, 'O2')[0]
co2_scrub_rating_string =iterative_elimanation(co2_scrubber_rating_list, 'CO2')[0]

o2_gen_rating = int(o2_gen_rating_string, 2)
co2_scrub_rating = int(co2_scrub_rating_string, 2)

print(o2_gen_rating * co2_scrub_rating) # 4636702