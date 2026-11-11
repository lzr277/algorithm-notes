from pathlib import Path
import subprocess,tempfile,random,itertools
p=Path(__file__).resolve().parent;build=Path(tempfile.mkdtemp(prefix='binary-tests-'));exes={};count=0
for f in (p/'代码').glob('*.cpp'):
 exe=build/(f.stem+'.exe');r=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(f),'-o',str(exe)],capture_output=True,text=True);assert r.returncode==0 and not r.stderr,r.stderr;exes[f.stem]=exe
def run(key,inp):
 global count
 count+=1;r=subprocess.run([str(exes[key])],input=inp,capture_output=True,text=True,timeout=8);assert r.returncode==0,r.stderr;return r.stdout.strip()
random.seed(11)
for _ in range(20):
 a=sorted(random.randint(0,15) for _ in range(random.randint(1,30)));q=list(range(18));expected=[a.index(x)+1 if x in a else -1 for x in q]
 assert list(map(int,run('P2249',f'{len(a)} {len(q)}\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,q))).split()))==expected
for _ in range(20):
 a=[random.randint(0,15) for _ in range(random.randint(1,30))];c=random.randint(1,10)
 expected=sum(x-y==c for x in a for y in a)
 assert int(run('P1102',f'{len(a)} {c}\n'+' '.join(map(str,a))))==expected
assert run('P1102','200000 1\n'+('0 '*100000)+('1 '*100000))=='10000000000'
for _ in range(20):
 a=[random.randint(1,30) for _ in range(random.randint(1,8))];m=random.randint(1,sum(a));expected=max(h for h in range(max(a)+1) if sum(max(0,x-h) for x in a)>=m)
 assert int(run('P1873',f'{len(a)} {m}\n'+' '.join(map(str,a))))==expected
assert run('P1873','3 2000000000\n1000000000 1000000000 1000000000')=='333333333'
for _ in range(20):
 a=random.sample(range(1,40),random.randint(2,8));m=random.randint(2,len(a))
 expected=max(min(v[i+1]-v[i] for i in range(m-1)) for v in itertools.combinations(sorted(a),m))
 assert int(run('P1824',f'{len(a)} {m}\n'+'\n'.join(map(str,a))))==expected
roots_cases=[[-100,0,100],[1,2,3],[-2.5,0.25,3.75],[-1,0,1],[-99.5,-98.5,99.75]]
for _ in range(15):
 roots_cases.append(sorted(random.sample(range(-85,86),3)))
for roots in roots_cases:
 x,y,z=roots;coeff=[1,-(x+y+z),x*y+x*z+y*z,-x*y*z];got=list(map(float,run('P1024',' '.join(map(str,coeff))).split()));assert len(got)==3,(roots,got)
 assert all(abs(a-b)<=0.0051 for a,b in zip(roots,got)),(roots,got)
(p/'验证报告.md').write_text(f'# 本地验证报告\n\n2026-11-11：5个C++17程序通过-Wall -Wextra编译，无警告；{count}组进程级测试通过。\n\n查找与线性扫描对比；数对与双重循环对比，另测答案10^10；砍树与逐高枚举对比，另测木材总量超过32位；奶牛与牛舍组合枚举对比；方程按已知三根反推系数，检查整点、端点、分数根和输出误差。\n\n本地测试不代表洛谷在线评测通过。\n',encoding='utf-8',newline='\n')
print('PASS',count,'program runs')
