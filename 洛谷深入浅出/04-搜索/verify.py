from pathlib import Path
import subprocess,tempfile,random,itertools
p=Path(__file__).resolve().parent;folder=Path(tempfile.mkdtemp(prefix='search-tests-'));exes={};count=0
for f in (p/'代码').glob('*.cpp'):
 exe=folder/(f.stem+'.exe');r=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(f),'-o',str(exe)],capture_output=True,text=True);assert r.returncode==0 and not r.stderr,r.stderr;exes[f.stem]=exe

def run(key,s):
 global count
 count+=1;r=subprocess.run([str(exes[key])],input=s,capture_output=True,text=True,timeout=15);assert r.returncode==0,r.stderr;return r.stdout.strip()
random.seed(12)
sol=[[1,2,3,4],[3,4,1,2],[2,1,4,3],[4,3,2,1]]
for _ in range(10):
 puzzle=[[x if random.random()<0.5 else 0 for x in row] for row in sol];out=run('例1-四阶数独','\n'.join(' '.join(map(str,r)) for r in puzzle));grid=[list(map(int,line.split())) for line in out.splitlines()];assert len(grid)==4
 for i in range(4):
  assert set(grid[i])=={1,2,3,4};assert {grid[j][i] for j in range(4)}=={1,2,3,4}
  for j in range(4):assert not puzzle[i][j] or puzzle[i][j]==grid[i][j]
 for x in [0,2]:
  for y in [0,2]:assert {grid[i][j] for i in range(x,x+2) for j in range(y,y+2)}=={1,2,3,4}
for puzzle in ['1 1 0 0\n0 0 0 0\n0 0 0 0\n0 0 0 0','1 2 3 0\n0 0 0 4\n0 0 0 0\n0 0 0 0']:
 assert run('例1-四阶数独',puzzle)=='No solution'
for n,total in [(4,2),(5,10),(6,4),(8,92),(13,73712)]:
 lines=run('P1219',str(n)).splitlines();assert int(lines[-1])==total;paths=[tuple(map(int,line.split())) for line in lines[:-1]];assert len(paths)==min(3,total) and paths==sorted(paths)
 for path in paths:
  assert len(set(path))==n
  assert all(abs(path[i]-path[j])!=j-i for i in range(n) for j in range(i+1,n))
for _ in range(12):
 subjects=[[random.randint(1,12) for _ in range(random.randint(1,8))] for _ in range(4)];best=0
 for a in subjects:
  best+=min(max(sum(a[i] for i in range(len(a)) if mask>>i&1),sum(a[i] for i in range(len(a)) if not(mask>>i&1))) for mask in range(1<<len(a)))
 inp=' '.join(str(len(a)) for a in subjects)+'\n'+'\n'.join(' '.join(map(str,a)) for a in subjects)
 assert int(run('P2392',inp))==best
for _ in range(12):
 n=random.randint(1,6);m=random.randint(1,6);sx=random.randrange(n);sy=random.randrange(m);d=[[999]*(n*m) for _ in range(n*m)]
 for x in range(n):
  for y in range(m):
   u=x*m+y;d[u][u]=0
   for dx,dy in [(1,2),(1,-2),(-1,2),(-1,-2),(2,1),(2,-1),(-2,1),(-2,-1)]:
    a=x+dx;b=y+dy
    if 0<=a<n and 0<=b<m:d[u][a*m+b]=1
 for k in range(n*m):
  for i in range(n*m):
   for j in range(n*m):d[i][j]=min(d[i][j],d[i][k]+d[k][j])
 got=list(map(int,run('P1443',f'{n} {m} {sx+1} {sy+1}').split()));assert got==[v if v<999 else -1 for v in d[sx*m+sy]]
for _ in range(16):
 n=random.randint(1,10);a=random.randint(1,n);b=random.randint(1,n);k=[random.randint(0,n) for _ in range(n)];d=[[999]*n for _ in range(n)]
 for i in range(n):
  d[i][i]=0
  for j in [i+k[i],i-k[i]]:
   if 0<=j<n and j!=i:d[i][j]=1
 for t in range(n):
  for i in range(n):
   for j in range(n):d[i][j]=min(d[i][j],d[i][t]+d[t][j])
 assert int(run('P1135',f'{n} {a} {b}\n'+' '.join(map(str,k))))==(d[a-1][b-1] if d[a-1][b-1]<999 else -1)
def meteor(events):
 death={}
 for x,y,t in events:
  for a,b in [(x,y),(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
   if a>=0 and b>=0:death[a,b]=min(death.get((a,b),999),t)
 current={(0,0)} if death.get((0,0),999)>0 else set()
 for t in range(max([e[2] for e in events]+[0])+2):
  if any(v not in death for v in current):return t
  current={(x+dx,y+dy) for x,y in current for dx,dy in [(1,0),(-1,0),(0,1),(0,-1)] if x+dx>=0 and y+dy>=0 and t+1<death.get((x+dx,y+dy),999)}
 return -1
cases=[[(0,0,0)],[(5,5,1)],[(0,0,2)],[(0,0,2),(1,0,1),(0,1,1)]]
cases += [[(random.randint(0,4),random.randint(0,4),random.randint(0,8)) for _ in range(random.randint(1,14))] for _ in range(20)]
for events in cases:
 inp=str(len(events))+'\n'+'\n'.join(f'{x} {y} {t}' for x,y,t in events);assert int(run('P2895',inp))==meteor(events),events
for _ in range(12):
 n=random.randint(1,8);edges=[(random.randrange(n),random.randrange(n)) for _ in range(random.randint(0,20))];d=[[999]*n for _ in range(n)]
 for i in range(n):d[i][i]=0
 for a,b in edges:d[a][b]=min(d[a][b],1)
 for k in range(n):
  for i in range(n):
   for j in range(n):d[i][j]=min(d[i][j],d[i][k]+d[k][j])
 assert int(run('AcWing847-图中点的层次',f'{n} {len(edges)}\n'+'\n'.join(f'{a+1} {b+1}' for a,b in edges)))==(d[0][-1] if d[0][-1]<999 else -1)
(p/'验证报告.md').write_text(f'# 本地验证\n\n2026-11-12：7个C++17程序无警告编译通过，{count}组进程测试通过。数独检查给定值保留和行列宫合法性、冲突与无解；皇后核对4/5/6/8/13的已知总数与输出合法性；左右脑与子集枚举对比；马/电梯/图BFS与Floyd全点对最短路对比；流星雨与逐时间层状态模拟对比，覆盖初始死亡、初始永久安全、严格截止和邻格影响。\n\n本地测试不代表在线评测通过。\n',encoding='utf-8',newline='\n')
print('PASS',count,'tests')
