from pathlib import Path
import subprocess,tempfile,itertools,random,functools
from fractions import Fraction
p=Path(__file__).resolve().parent
build=Path(tempfile.mkdtemp(prefix='greedy-check-'));exes={};count=0
for f in (p/'代码').glob('*.cpp'):
 exe=build/(f.stem+'.exe')
 r=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(f),'-o',str(exe)],capture_output=True,text=True)
 assert r.returncode==0 and not r.stderr,r.stderr
 exes[f.stem]=exe

def run(key,s):
 global count
 r=subprocess.run([str(exes[key])],input=s,capture_output=True,text=True,timeout=5);assert r.returncode==0
 count+=1;return r.stdout.strip()
random.seed(8)
for case in range(12):
 n=random.randint(1,6);t=random.randint(1,12);a=[(random.randint(1,9),random.randint(1,20)) for _ in range(n)]
 best=Fraction(0)
 for mask in range(1<<n):
  w=sum(a[i][0] for i in range(n) if mask>>i&1);v=sum(a[i][1] for i in range(n) if mask>>i&1)
  if w>t:continue
  best=max(best,Fraction(v))
  for i,(m,value) in enumerate(a):
   if not(mask>>i&1):best=max(best,Fraction(v)+Fraction(min(m,t-w)*value,m))
 got=float(run('P2240',f'{n} {t}\n'+'\n'.join(f'{m} {v}' for m,v in a)))
 assert abs(got-float(best))<=0.0051,(a,got,best)
for case in range(12):
 n=random.randint(1,6);a=[random.randint(1,9) for _ in range(n)]
 def wait(order):return sum(a[order[i]]*(n-i-1) for i in range(n))
 best=min(wait(order) for order in itertools.permutations(range(n)))
 out=run('P1223',str(n)+'\n'+' '.join(map(str,a))).splitlines();ids=list(map(int,out[0].split()))
 assert ids==sorted(range(1,n+1),key=lambda i:(a[i-1],i))
 assert abs(float(out[1])-best/n)<=0.0051
for case in range(16):
 n=random.randint(1,8);a=[]
 for _ in range(n):
  l=random.randint(0,8);a.append((l,l+random.randint(1,5)))
 best=0
 for mask in range(1<<n):
  chosen=sorted(a[i] for i in range(n) if mask>>i&1)
  if all(chosen[i-1][1]<=chosen[i][0] for i in range(1,len(chosen))):best=max(best,len(chosen))
 assert int(run('P1803',str(n)+'\n'+'\n'.join(f'{l} {r}' for l,r in a)))==best
@functools.lru_cache(None)
def optimal(a):
 if len(a)==1:return 0
 ans=10**30
 for i in range(len(a)):
  for j in range(i+1,len(a)):
   s=a[i]+a[j];b=tuple(sorted([a[k] for k in range(len(a)) if k!=i and k!=j]+[s]))
   ans=min(ans,s+optimal(b))
 return ans
for case in range(12):
 n=random.randint(1,6);a=[random.randint(1,20) for _ in range(n)];expected=optimal(tuple(sorted(a)));inp=str(n)+'\n'+' '.join(map(str,a))
 for key in ['P1090','例4-分卷子教学模型']:assert int(run(key,inp))==expected
 out=run('例6-哈夫曼编码教学模型',inp).splitlines();assert int(out[0])==expected
 codes=out[1:];assert len(codes)==n
 if n==1:assert codes==['(empty)']
 else:
  assert all(set(s)<=set('01') for s in codes)
  assert all(not codes[j].startswith(codes[i]) for i in range(n) for j in range(n) if i!=j)
  assert sum(a[i]*len(codes[i]) for i in range(n))==expected
assert run('P1090','1\n9')=='0'
assert run('P1803','2\n0 1\n1 2')=='2'
assert run('P2240','3 50\n10 60\n20 100\n30 120')=='240.00'
# Additional screenshot problems: independent exhaustive references.
for case in range(8):
 n=random.randint(2,5);x=random.randint(0,5);a=[random.randint(0,4) for _ in range(n)]
 best=min(sum(a)-sum(b) for b in itertools.product(*(range(v+1) for v in a)) if all(b[i-1]+b[i]<=x for i in range(1,n)))
 assert int(run('P3817',f'{n} {x}\n'+' '.join(map(str,a))))==best
for case in range(8):
 s=''.join(str(random.randint(0,9)) for _ in range(6));s='1'+s[1:];k=random.randint(1,5)
 best=min(int(''.join(s[i] for i in ids)) for ids in itertools.combinations(range(len(s)),len(s)-k))
 assert run('P1106',s+'\n'+str(k))==str(best)
for case in range(8):
 n=6;strength=random.randint(0,12);height=5;apples=[(random.randint(1,10),random.randint(0,8)) for _ in range(n)]
 best=0
 for mask in range(1<<n):
  selected=[apples[i] for i in range(n) if mask>>i&1]
  if all(h<=height for h,c in selected) and sum(c for h,c in selected)<=strength:best=max(best,len(selected))
 assert int(run('P1478',f'{n} {strength}\n2 3\n'+'\n'.join(f'{h} {c}' for h,c in apples)))==best
@functools.lru_cache(None)
def road(a):
 if not any(a):return 0
 best=sum(a)
 for l in range(len(a)):
  for r in range(l,len(a)):
   if min(a[l:r+1])==0:break
   b=list(a)
   for i in range(l,r+1):b[i]-=1
   best=min(best,1+road(tuple(b)))
 return best
for case in range(8):
 a=tuple(random.randint(0,3) for _ in range(4))
 assert int(run('P5019','4\n'+' '.join(map(str,a))))==road(a)
for case in range(8):
 suppliers=[(random.randint(0,8),random.randint(0,5)) for _ in range(4)];need=random.randint(0,sum(c for v,c in suppliers))
 best=min(sum(q*v for q,(v,c) in zip(qs,suppliers)) for qs in itertools.product(*(range(c+1) for v,c in suppliers)) if sum(qs)==need)
 assert int(run('P1208',f'{need} 4\n'+'\n'.join(f'{v} {c}' for v,c in suppliers)))==best
@functools.lru_cache(None)
def pairs(a,w):
 if not a:return 0
 best=1+pairs(a[:-1],w)
 for i in range(len(a)-1):
  if a[i]+a[-1]<=w:best=min(best,1+pairs(a[:i]+a[i+1:-1],w))
 return best
for case in range(8):
 a=tuple(sorted(random.randint(5,20) for _ in range(7)));w=25
 assert int(run('P1094',f'{w}\n7\n'+' '.join(map(str,a))))==pairs(a,w)
for case in range(8):
 a=random.sample(range(1,20),6)
 best=max(sum((order[i]-(order[i-1] if i else 0))**2 for i in range(6)) for order in itertools.permutations(a))
 assert int(run('P4995','6\n'+' '.join(map(str,a))))==best
@functools.lru_cache(None)
def groups(values,state=()):
 if not values:return min(length for end,length in state)
 x=values[0];choices={tuple(sorted(state+((x,1),)))}
 for i,(end,length) in enumerate(state):
  if end==x-1:choices.add(tuple(sorted(state[:i]+state[i+1:]+((x,length+1),))))
 return max(groups(values[1:],s) for s in choices)
for case in range(12):
 n=random.randint(1,8);a=tuple(sorted(random.randint(-2,3) for _ in range(n)))
 assert int(run('P4447',str(n)+'\n'+' '.join(map(str,a))))==groups(a)
for case in range(8):
 n=5;king=random.randint(1,8);a=[(random.randint(1,8),random.randint(1,8)) for _ in range(n)]
 def reward(order):
  product=king;best=0
  for left,right in order:best=max(best,product//right);product*=left
  return best
 best=min(reward(order) for order in itertools.permutations(a))
 assert int(run('P1080',f'{n}\n{king} 1\n'+'\n'.join(f'{x} {y}' for x,y in a)))==best
assert run('P1080','1000\n9999 1\n'+('9999 9999\n'*1000))==str(9999**999)
for case in range(8):
 a=[str(random.randint(1,999)) for _ in range(6)]
 best=max(''.join(order) for order in itertools.permutations(a))
 assert run('P1012','6\n'+' '.join(a))==best
print('PASS: ten added problem families checked independently')

(p/'验证报告.md').write_text(f'# 本地验证报告\n\n2026-11-08：16份C++17程序通过 -Wall -Wextra 编译，无警告。{count}组进程级测试通过。部分背包与分数顶点枚举交叉验证，排队与全排列对比，区间选择与子集枚举对比，合并与全部两两合并顺序递归对比；编码另检查前缀无冲突和频次×码长等于最优WPL。包括单物品/单符号、端点相接与并列情况。\n\n本地测试不代表洛谷在线评测通过。分卷子和编码制定为明确假设的教学模型。\n',encoding='utf-8',newline='\n')
print('PASS',count,'process tests')
