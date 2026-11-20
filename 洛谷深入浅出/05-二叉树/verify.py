from pathlib import Path
import subprocess,tempfile,random,itertools,functools,collections
p=Path(__file__).resolve().parent;folder=Path(tempfile.mkdtemp(prefix='tree-tests-'));exes={};count=0
for f in (p/'代码').glob('*.cpp'):
 exe=folder/(f.stem+'.exe');r=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(f),'-o',str(exe)],capture_output=True,text=True);assert r.returncode==0 and not r.stderr,r.stderr;exes[f.stem]=exe

def run(key,inp):
 global count
 count+=1;r=subprocess.run([str(exes[key])],input=inp,capture_output=True,text=True,timeout=15);assert r.returncode==0,r.stderr;return r.stdout
random.seed(20)
for _ in range(20):
 n=random.randint(1,15);ids=list(range(1,n+1));random.shuffle(ids);root=ids[0];lc=[0]*(n+1);rc=[0]*(n+1);slots=[(root,0),(root,1)]
 for u in ids[1:]:
  index=random.randrange(len(slots));v,side=slots.pop(index);(lc if side==0 else rc)[v]=u;slots.extend([(u,0),(u,1)])
 def order(u,kind):
  if not u:return []
  a=order(lc[u],kind);b=order(rc[u],kind)
  return ([u]+a+b) if kind=='pre' else (a+[u]+b) if kind=='in' else (a+b+[u])
 def height(u):return 0 if not u else 1+max(height(lc[u]),height(rc[u]))
 q=[root]
 for u in q:
  if lc[u]:q.append(lc[u])
  if rc[u]:q.append(rc[u])
 expected=[order(root,k) for k in ['pre','in','post']]+[q]
 inp=str(n)+'\n'+'\n'.join(f'{i} {lc[i]} {rc[i]}' for i in range(1,n+1))
 for key in ['00-建树与四种遍历','01-显式栈与队列遍历']:
  lines=run(key,inp).splitlines();assert [list(map(int,line.split())) for line in lines[:4]]==expected
  if key.startswith('00'):assert int(lines[4])==height(root)
 letters={u:chr(64+u) for u in ids};pre=''.join(letters[u] for u in expected[0]);ino=''.join(letters[u] for u in expected[1]);post=''.join(letters[u] for u in expected[2]);assert run('P1827',ino+'\n'+pre).strip()==post
 # Depth problem requires root 1: reindex the same topology.
 mapping={u:i+1 for i,u in enumerate(ids)};childlines=[]
 for u in ids:childlines.append(f'{mapping.get(lc[u],0)} {mapping.get(rc[u],0)}')
 assert int(run('P4913',str(n)+'\n'+'\n'.join(childlines)))==height(root)
 assert run('P1229',pre.lower()+'\n'+post.lower()).strip()==str(2**sum(bool(lc[u])!=bool(rc[u]) for u in ids))
assert run('00-建树与四种遍历','0\n').splitlines()==['','','','','0']
assert run('01-显式栈与队列遍历','0\n').splitlines()==['','','','']
n=100000;chain=str(n)+'\n'+'\n'.join(f'0 {i+1}' if i<n else '0 0' for i in range(1,n+1));assert int(run('P4913',chain))==n
chain2=str(n)+'\n'+'\n'.join(f'{i} 0 {i+1}' if i<n else f'{i} 0 0' for i in range(1,n+1));lines=run('01-显式栈与队列遍历',chain2).splitlines();assert list(map(int,lines[0].split()))==list(range(1,n+1));assert list(map(int,lines[2].split()))==list(range(n,0,-1))
for _ in range(12):
 k=random.randint(1,7);a=random.sample(range(1,10000),1<<k);current=list(range(len(a)))
 while len(current)>2:current=[x if a[x]>a[y] else y for x,y in zip(current[::2],current[1::2])]
 x,y=current;expected=(x if a[x]<a[y] else y)+1;assert int(run('P4715',str(k)+'\n'+' '.join(map(str,a))))==expected
for _ in range(12):
 n=random.randint(1,10);lc=[0]*(n+1);rc=[0]*(n+1);slots=[(1,0),(1,1)];dist=[[999]*n for _ in range(n)]
 for i in range(n):dist[i][i]=0
 for u in range(2,n+1):
  v,side=slots.pop(random.randrange(len(slots)));(lc if side==0 else rc)[v]=u;slots.extend([(u,0),(u,1)]);dist[u-1][v-1]=dist[v-1][u-1]=1
 w=[random.randint(0,30) for _ in range(n)]
 for k in range(n):
  for i in range(n):
   for j in range(n):dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j])
 expected=min(sum(w[j]*dist[i][j] for j in range(n)) for i in range(n));inp=str(n)+'\n'+'\n'.join(f'{w[i-1]} {lc[i]} {rc[i]}' for i in range(1,n+1));assert int(run('P1364',inp))==expected
ops=[];expected=[];values=[]
for _ in range(100):
 op=random.randint(1,3);x=random.randint(-10,10)
 if op==1:ops.append(f'1 {x}');values.append(x)
 elif op==2:ops.append(f'2 {x}');expected.append([int(x in values)])
 else:ops.append('3');expected.append(sorted(values))
assert [list(map(int,line.split())) for line in run('BST-插入与查询',str(len(ops))+'\n'+'\n'.join(ops)).splitlines()]==expected
for inp,pre,ino in [('ab-','-ab','(a-b)'),('ab/c*','*/abc','((a/b)*c)'),('ab+c*','*+abc','((a+b)*c)'),('abcd*+-','-a+b*cd','(a-(b+(c*d)))')]:assert run('表达式树-后缀建树',inp).splitlines()==[pre,ino,inp]
# Enumerate every ordered binary shape up to 5 nodes, assign distinct preorder labels,
# group by the resulting preorder/postorder and compare the number of shapes.
@functools.lru_cache(None)
def shapes(n):
 if n==0:return (None,)
 return tuple((l,r) for k in range(n) for l in shapes(k) for r in shapes(n-1-k))
for n in range(1,6):
 groups=collections.Counter()
 for shape in shapes(n):
  counter=[0]
  def encode(t):
   if t is None:return ''
   ch=chr(97+counter[0]);counter[0]+=1;left=encode(t[0]);right=encode(t[1]);return left+right+ch
  groups[encode(shape)]+=1
 for post,total in groups.items():assert int(run('P1229',''.join(chr(97+i) for i in range(n))+'\n'+post))==total
(p/'验证报告.md').write_text(f'# 本地验证报告\n\n2026-11-20：9个C++17程序通过-Wall -Wextra编译，无警告；{count}组进程级测试通过。\n\n随机合法树覆盖非1根、各种缺失孩子；递归/显式栈四序与独立参考相同；深度测试10万节点链；美国血统与已知遍历对比；遍历问题另枚举1..5节点全部形状核对歧义计数；淘汰赛按真实轮次模拟核对；医院与Floyd距离对比；BST核对重复/负数/插入查询；表达式检查左右顺序和括号语义。\n\n本地测试不代表洛谷在线评测通过。\n',encoding='utf-8',newline='\n')
print('PASS',count,'process tests')
