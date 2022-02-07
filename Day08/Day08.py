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

print(unique_digit_count) # 512

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

total = 0

for entry in entries:
    left_hand_values, right_hand_values = entry
    nums = find_nums(left_hand_values)
    output_value = get_output_values(right_hand_values,nums)
    total+=output_value

print(total) # 1091165