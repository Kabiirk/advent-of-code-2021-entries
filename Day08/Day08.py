entries  = []
with open('input.txt', 'r') as f:
    for line in f:
        temp = line.strip().split(' | ')
        signal_pattern = temp[0].split(' ')
        outputs = temp[1].split(' ')
        entries.append([signal_pattern, outputs])

# Part 1
unique_digit_count = 0
for entry in entries:
    outputs = entry[1]
    for output in outputs:
        # 1, 4, 8, 7
        if(len(output) == 2 or \
            len(output) == 4 or \
            len(output) == 3 or \
            len(output) == 7):
            unique_digit_count+=1

print(unique_digit_count)

# Part 2
def find_nums(left_hand_values):
    nums = dict()
    segments = dict()

    uniques = {1:2,7:3,4:4,8:7}
    for num,len_num in uniques.items():
        nums[num] = [x for x in left_hand_values if len(x) == len_num].pop()

    segments[1] = (set(nums[7]) - set(nums[1])).pop()

    nums[9] = [x for x in left_hand_values if len(x) == 6 and set(nums[4] + segments[1]) < set(x)].pop()
    segments[7] = (set(nums[9]) - set(nums[4] + segments[1])).pop()

    nums[3] = [x for x in left_hand_values if len(x) == 5 and set(nums[7] + segments[7]) < set(x)].pop()
    segments[4] = (set(nums[3]) - set(nums[7]+segments[7])).pop()
    segments[2] = (set(nums[9]) - set(nums[3])).pop()

    nums[5] = [x for x in left_hand_values if len(x) == 5 and set(segments.values()) < set(x)].pop()
    segments[6] = (set(nums[5]) - set(segments.values())).pop()
    
    nums[6] = [x for x in left_hand_values if len(x) == 6 and set(segments.values()) < set(x) and x != nums[9]].pop()
    segments[5] = (set(nums[6]) - set(segments.values())).pop()
    segments[3] = (set(nums[8]) - set(segments.values())).pop()
    
    nums[2] = ''.join(segments[x] for x in [1,3,4,5,7])
    nums[0] = ''.join(segments[x] for x in [1,2,3,5,6,7])

    return {''.join(sorted(value)):key for key,value in nums.items()}

def get_output_values(right_hand_values, nums):
    output_num = 0
    for index, value in enumerate(right_hand_values[-1::-1]):
        value_sorted = ''.join(sorted(value))
        output_num += nums[value_sorted] * (10**index)
    return output_num

def main():
    with open('input.txt','r') as infile:
        display_values = [(sides[0].split(),sides[1].split()) for sides in (line.strip().split(" | ") for line in infile.readlines())]

    total = 0

    for entry in display_values:
        left_hand_values, right_hand_values = entry
        nums = find_nums(left_hand_values)
        output_value = get_output_values(right_hand_values,nums)
        total+=output_value

    print(total)

main()

class seven_seg_display:
    display = {
        'a':False,
        'b':False,
        'c':False,
        'd':False,
        'e':False,
        'f':False,
        'g':False,
        }
    def __init__(self):
        pass

    def set_display(self, string):
        for letter in string:
            self.display[letter] = True

    def get_number(self, string):
        # Mapping :
        #
        #   dddd
        #  e    a
        #  e    a
        #   ffff
        #  g    b
        #  g    b
        #   cccc
        self.set_display(string)
        # Unique numbers
        if(len(string) == 2):
            return '1'
        if(len(string) == 4):
            return '4'
        if(len(string) == 3):
            return '7'
        if(len(string) == 7):
            return '8'

        a = self.display['a']
        b = self.display['b']
        c = self.display['c']
        d = self.display['d']
        e = self.display['e']
        f = self.display['f']
        g = self.display['g']
        # 0
        if( a and b and c and d and e and not( f) and g ):
            return '0'
        # 1
        # if( a and b and not c and not d and not e and not f and not g ):
        #     return '1'
        # 2
        if( a and not( b )and c and d and not( e) and f and g ):
            return '2'
        # 3
        if( a and b and c and d and not( e) and f and not( g) ):
            return '3'
        # 4
        # if( a and b and not c and not d and e and f and not g ):
        #     return '4'
        # 5
        if( not( a) and b and c and d and e and f and not( g) ):
            return '5'
        # 6
        if( not(a) and b and c and d and e and f and g ):
            return '6'
        # 7
        # if( a and b and c and d and not e and not f and not g ):
        #     return '7'
        # 8
        # if( a and b and c and d and e and f and g ):
        #     return '8'
        # 9
        if( a and b and c and d and e and f and not(g) ):
            return '9'

        return '1'

    def clear_display(self):
        for key in self.display:
            self.display[key] = False

display = seven_seg_display()

decoded = []
final_sum = 0
for entry in entries:
    outputs = entry[1]
    code = ''
    for output in outputs:
        code += display.get_number(output)
        display.clear_display()
    final_sum += int(code)
print(final_sum) # 1091165

# op = ['fdgacbe', 'cefdb', 'cefbgd', 'gcbe']
# code = ''

# s = 'fcgedb'
# print(display.get_number(s))
# print(display.display)
# display.clear_display()

# for o in op:
#     code += display.get_number(o)
#     display.clear_display()
# print(code)
