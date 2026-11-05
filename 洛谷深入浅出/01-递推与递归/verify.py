from pathlib import Path
import subprocess,math,tempfile,random
p=Path(__file__).resolve().parent
exes={}; build=Path(tempfile.mkdtemp(prefix='luogu-verify-'))
for src in (p/'代码').glob('*.cpp'):
    exe=build/(src.stem+'.exe');r=subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-O2',str(src),'-o',str(exe)],capture_output=True,text=True)
    assert r.returncode==0,r.stderr
    assert not r.stderr,r.stderr
    exes[src.stem]=exe
count=0
def check(key,inp,expected):
    global count
    r=subprocess.run([str(exes[key])],input=inp,text=True,capture_output=True,timeout=8)
    assert r.returncode==0 and r.stdout.strip()==str(expected).strip(),(key,inp,r.stdout,expected,r.stderr)
    count+=1
check('01-知识点演示', '', 'knowledge checks passed')
for n in [0,1,5,20]:
    a,b=0,1
    for _ in range(n):a,b=b,a+b
    check('00-入门',str(n),f'{n*(n+1)//2}\n{math.factorial(n)}\n{a}\n{a}\n{a}')
for n in [1,2,5,50,5000]:
    a,b=1,1
    for _ in range(2,n+1):a,b=b,a+b
    check('P1255',str(n),b)
for n in [1,3,18]:check('P1044',str(n),math.comb(2*n,n)//(n+1))
for n in [1,6,10,1000]:
    f=[0]*(n+1)
    for i in range(1,n+1):f[i]=1+sum(f[1:i//2+1])
    check('P1028',str(n),f[n])
for n,m,hx,hy in [(6,6,3,3),(2,2,1,1),(20,20,20,0),(3,4,0,0)]:
    # Independent path enumeration via memoized search.
    from functools import lru_cache
    forbidden={(hx,hy)}|{(hx+dx,hy+dy) for dx,dy in [(1,2),(1,-2),(-1,2),(-1,-2),(2,1),(2,-1),(-2,1),(-2,-1)]}
    @lru_cache(None)
    def paths(x,y):
        if (x,y) in forbidden:return 0
        if (x,y)==(n,m):return 1
        return (paths(x+1,y) if x<n else 0)+(paths(x,y+1) if y<m else 0)
    check('P1002',f'{n} {m} {hx} {hy}',paths(0,0))
# Independent bottom-up Function reference table.
w=[[[1]*21 for _ in range(21)] for _ in range(21)]
for a in range(1,21):
 for b in range(1,21):
  for c in range(1,21):
   w[a][b][c]=(w[a][b][c-1]+w[a][b-1][c-1]-w[a][b-1][c]) if a<b<c else (w[a-1][b][c]+w[a-1][b-1][c]+w[a-1][b][c-1]-w[a-1][b-1][c-1])
cases=[(1,1,1),(20,20,20),(-1,100,100),(21,3,5),(-9223372036854775808,9223372036854775807,1)]
random.seed(0);cases += [tuple(random.randint(-2,23) for _ in range(3)) for _ in range(30)]
expected=[]
for a,b,c in cases:
 ans=1 if min(a,b,c)<=0 else w[20][20][20] if max(a,b,c)>20 else w[a][b][c]
 expected.append(f'w({a}, {b}, {c}) = {ans}')
check('P1464','\n'.join(' '.join(map(str,c)) for c in cases)+'\n-1 -1 -1\n','\n'.join(expected))
for inp,out in [('ABC','ABC'),('[3AB]','AB'*3),('A[2B[3C]]','ABCCCBCCC'),('[12A]','A'*12),('[2[2[2CB]]]','CB'*8),('[99[99AB]]','AB'*9801)]:check('P1928',inp,out)
(p/'验证报告.md').write_text(f'''# 验证报告\n\n2026-11-05：{len(exes)} 个 C++17 程序通过 g++ -Wall -Wextra -O2 编译，无警告；{count} 组进程级测试全部通过，其中 Function 单组进程包含 {len(cases)} 个查询。\n\n覆盖：入门的 0/1/5/20、楼梯 5000 阶高精度、栈 18、数的计算 1000、马控制点与棋盘边界、Function 大整数输入与边界顺序、外星密码两位次数与多层嵌套。Function 使用独立自底向上表交叉验证。\n\n这是本地验证，不代表已提交洛谷或通过在线评测。\n''',encoding='utf-8')
print('PASS',count,'process tests;',len(cases),'Function queries')
