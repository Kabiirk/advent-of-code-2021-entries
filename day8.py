entries  = []
with open('input8.txt', 'r') as f:
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

    def get_number(self):
        # Mapping :
        #
        #   dddd
        #  e    a
        #  e    a
        #   ffff
        #  g    b
        #  g    b
        #   cccc

        # 0
        if(self.display['d'] and self.display['a'] and\
            self.display['b'] and self.display['c'] and\
            self.display['g'] and self.display['e']
            ):
            return '0'
        # 1
        if(self.display['a'] and self.display['b']):
            return '1'
        # 2
        if(self.display['d'] and self.display['a'] and\
            self.display['f'] and self.display['g'] and\
            self.display['c'] ):
            return '2'
        # 3
        if(self.display['d'] and self.display['a'] and\
            self.display['f'] and self.display['b'] and\
            self.display['c'] ):
            return '3'
        # 4
        if(self.display['e'] and self.display['f'] and\
            self.display['a'] and self.display['b'] ):
            return '0'
        # 5
        if(self.display['d'] and self.display['e'] and\
            self.display['f'] and self.display['b'] and\
            self.display['c'] ):
            return '5'
        # 6
        if(self.display['d'] and self.display['e'] and\
            self.display['g'] and self.display['c'] and\
            self.display['b'] and self.display['f']):
            return '6'
        # 7
        if(self.display['d'] and self.display['a'] and\
            self.display['b'] ):
            return '7'
        # 8
        if(self.display['d'] and self.display['a'] and\
            self.display['b'] and self.display['c'] and\
            self.display['g'] and self.display['e'] and\
            self.display['f']
            ):
            return '8'
        # 9
        if(self.display['d'] and self.display['a'] and\
            self.display['e'] and self.display['f'] and\
            self.display['a'] and self.display['c'] and \
            self.display['b'] ):
            return '9'

        return f'{self.display} No digit Set !'

    def clear_display(self):
        for key in self.display:
            self.display[key] = False

display = seven_seg_display()

decoded = []
# for entry in entries:
#     outputs = entry[1]
#     code = ''
#     for output in outputs:
#         display.set_display(output)
#         code += display.get_number()
#         display.clear_display()
#     print(code)

op = ['fdgacbe', 'cefdb', 'cefbgd', 'gcbe']
for o in op:
    display.set_display(o)
    print(display.get_number())
    display.clear_display()