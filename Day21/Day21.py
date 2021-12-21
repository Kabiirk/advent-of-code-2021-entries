import sys
import itertools as it
import functools as ft
import collections as clc
import re
import math
import datetime as dt
import time

file=open('input.txt',"r")
pl1=int(file.readline().rpartition(' ')[2])
pl2=int(file.readline().rpartition(' ')[2])
pl=[pl1,pl2]
sc=[0,0]

#part1 

dice_length=100
roll_how_many=3
win_at=1000
index=0
cyc=it.cycle(range(1,100+1))
cyc_iter=cyc.__iter__()
while True:
  index+=roll_how_many
  # print(i)
  player_num=1-(index%2)
  pl[player_num]+=sum(cyc_iter.__next__() for _ in range(roll_how_many))
  pl[player_num]%=10
  if pl[player_num]==0:
    pl[player_num]=10
  sc[player_num]+=pl[player_num]
  # print(sc)
  if sc[player_num]>=win_at:
    break


# print(sc[1-player_num],sc[player_num],index)
print(sc[1-player_num]*index)

#part 2
dice_length=3
win_at=21
value=clc.Counter(sum(i) for i in it.product(range(1,dice_length+1),repeat=roll_how_many))

cases={}
for i in range(3,10):
  for j in range(1,11):
    new_val=(i+j)%10
    if new_val==0:
      new_val=10
    if cases.get((new_val,i)) is not None:
      print("failed at",new_val,i,j)
      exit(-1)
    cases[(new_val,i)]=j



dp=clc.defaultdict(lambda :-1)
start_tuple=(0,0,pl1,pl2,0) # score1 score2 pos1 pos2 whose_turn
dp[start_tuple]=1


def func(tup,should_be_winning=False):

  if min(tup[:2])<0:
    return 0
  if max(tup[:2])>=win_at and not should_be_winning:
    return 0
  if dp[tup]!=-1:
    return dp[tup]
  prev_turn=1-tup[-1]
  ans=0
  for i in value.items():
    new_l=list(tup)    

    new_l[prev_turn]-=new_l[prev_turn+2]
    new_l[2+prev_turn]=cases[(new_l[2+prev_turn],i[0])]

    new_l[-1]=1-new_l[-1]
    ans+=i[1]*func(tuple(new_l))
  dp[tup]=ans
  return ans

maxi=win_at-1+10
all_pos=list(it.product(range(1,11),repeat=2))
winner0=0
winner1=0
for i in reversed(list(range(win_at,maxi+1))):
  for j in range(0,win_at):
    for k in all_pos:
      winner0+=func((i,j,k[0],k[1],1),True)

for j in range(win_at,maxi+1):
  for i in range(0,win_at):
    for k in all_pos:
      winner1+=func((i,j,k[0],k[1],0),True)
  
print(max(winner1,winner0))