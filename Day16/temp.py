with open('input.txt') as fi:
    hex_stream=fi.read()[:-1]
print("hex_stream", hex_stream, len(hex_stream))

transmission = ''
for h in hex_stream:
    x = bin(int(h,base=16))
    #print(h,len(x))
    transmission += '0'*(6-len(x)) +str(x)[2:]

print("transmission", transmission, len(transmission))

def literal(trans):
    number = ''
    while True:
        number += trans[1:5]
        x = trans[0]
        trans = trans[5:]
        if x =='0':
            break
    print("number", number)
    return int(number,2),trans

a = []
def packet(trans):
    pversion,ptype,rest = int(trans[:3],2),int(trans[3:6],2),trans[6:]
    a = []
    versions,result = 0,0
    if ptype == 4:
        result, rest = literal(rest)
    elif ptype != 4:
        x = rest[0]
        rest = rest[1:]
        subpackets = []
        if x == '0':        #next 15 bits are a number that represents the total length in bits of the sub-packets contained by this packet.
            subpacked_length = int(rest[:15],2)
            rest = rest[15:]
            estimatedrestlength = len(rest) - subpacked_length
            while len(rest)>estimatedrestlength:
                subpacket, rest = packet(rest)
                for sub in subpacket: subpackets.append(sub)
        elif x == '1':       #next 11 bits are a number that represents the number of sub-packets immediately contained by this packet
            subpacked_count= int(rest[:11],2)
            rest = rest[11:]
            for _ in range(subpacked_count):
                subpacket, rest = packet(rest)
                for sub in subpacket: subpackets.append(sub)
        for x in subpackets:
            versions += x[0]
        subresults=[]
        if ptype ==0:  #Addition
            for x in subpackets:
                result +=x[2]
        elif ptype ==1:
            result = 1
            for x in subpackets:
                result *=x[2]
        elif ptype ==2:
            for x in subpackets:
                subresults += [x[2]]
            result = min(subresults)
        elif ptype ==3:
            for x in subpackets:
                subresults += [x[2]]
            result = max(subresults)
        elif ptype ==5:
            if subpackets[0][2]>subpackets[1][2]: 
                result = 1 
        elif ptype ==6:
            if subpackets[0][2]<subpackets[1][2]: 
                result = 1 
        elif ptype ==7:
            if subpackets[0][2]==subpackets[1][2]: 
                result = 1 
    a.append((pversion+versions,ptype,result))
    print("a", a)
    return a , rest

packets, rest = packet(transmission)
print("packets", packets)
print("rest", rest)

# Part 1
print(packets[-1][0])# 971

# Part 2
print(packets[-1][2])# 831996589851