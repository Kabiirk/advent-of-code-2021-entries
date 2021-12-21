t = [l.strip() for l in open("input.txt","rt")]
a = [e=='#' for e in t[0]]
m = {(r,c) for r,l in enumerate(t[2:]) for c,x in enumerate(l) if x=='#'}
N = max(r for r,_ in m)+1; assert N==max(c for _,c in m)+1

def step(m):
  n = set()
  for r in range(-N-1,2*N+1): # it works but there should be a better approach
    for c in range(-N-1,2*N+1):
      k = ''.join(str(int((r+i,c+j) in m)) for i in (-1,0,1) for j in (-1,0,1))
      if a[int(k,2)]:
        n.add((r,c))
  return n

def solve(m,n):
  for i in range(n): m = step(m)
  return sum(int((r,c) in m) for r in range(-2-n,N+2+n) for c in range(-2-n,N+2+n))

print( solve( m.copy(), 2 ) )
print( solve( m, 50 ) )