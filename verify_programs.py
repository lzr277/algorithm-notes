"""独立程序的固定边界测试和小规模随机对照测试。无第三方依赖。"""
from pathlib import Path
import collections, itertools, json, os, random, shutil, subprocess
ROOT=Path(__file__).resolve().parent
CODES=ROOT/'算法学习手册/代码'
BUILD=ROOT/'.build'
def verify():
    compiler=os.environ.get('CXX') or shutil.which('g++')
    if not compiler: raise SystemExit('GNU C++17 compiler missing; set CXX. Tests NOT run.')
    BUILD.mkdir(exist_ok=True)
    counts={}; executables={}
    for path in sorted(CODES.glob('*.cpp')):
        key=path.stem.split('-')[0]; exe=BUILD/(key+('.exe' if os.name=='nt' else ''))
        proc=subprocess.run([compiler,'-std=c++17','-O2','-Wall','-Wextra','-pedantic',str(path),'-o',str(exe)],capture_output=True,text=True)
        if proc.returncode or proc.stderr: raise AssertionError(f'{path.name}: {proc.stderr}')
        executables[key]=exe;counts[key]=0
    def run(key,inp,expected):
        proc=subprocess.run([str(executables[key])],input=inp,capture_output=True,text=True,timeout=5)
        assert proc.returncode==0,(key,inp,proc.stderr)
        assert proc.stdout.split()==str(expected).split(),(key,inp,proc.stdout,expected)
        counts[key]+=1
    rng=random.Random(20261012)
    for a in [[],[7],[2]*50,list(range(100)),list(range(100,0,-1)),[-2147483648,0,2147483647]]+[[rng.randint(-20,20) for _ in range(rng.randrange(30))] for _ in range(50)]:
        run('785',f'{len(a)}\n'+ ' '.join(map(str,a)), ' '.join(map(str,sorted(a))))
    for _ in range(50):
        a=sorted(rng.randint(-8,8) for _ in range(rng.randrange(30)));queries=list(range(-10,11))
        answers=[]
        for q in queries:
            positions=[i for i,x in enumerate(a) if x==q]
            answers.append(f'{positions[0]} {positions[-1]}' if positions else '-1 -1')
        run('789',f'{len(a)} {len(queries)}\n'+' '.join(map(str,a))+'\n'+'\n'.join(map(str,queries)),'\n'.join(answers))
    run('836','3 6\nM 1 2\nM 2 1\nQ 1 2\nQ 1 3\nM 2 3\nQ 1 3','Yes No Yes')
    for _ in range(30):
        n=10; label=list(range(n+1)); ops=[];expected=[]
        for j in range(60):
            a,b=rng.randint(1,n),rng.randint(1,n)
            if rng.random()<.5:
                ops.append(f'M {a} {b}');old,new=label[a],label[b]
                label=[new if x==old else x for x in label]
            else:ops.append(f'Q {a} {b}');expected.append('Yes' if label[a]==label[b] else 'No')
        run('836',f'{n} {len(ops)}\n'+'\n'.join(ops),' '.join(expected))
    run('847','1 0','0');run('847','3 1\n1 2','-1')
    for _ in range(40):
        n=8;edges=[(a,b) for a in range(1,n+1) for b in range(1,n+1) if rng.random()<.15]
        # 参考实现枚举从起点可达的每一层顶点集合。
        frontier={1};seen={1};distance=0;ans=0 if n==1 else -1
        while frontier and n not in frontier:
            frontier={b for a,b in edges if a in frontier and b not in seen};seen|=frontier;distance+=1
            if n in frontier:ans=distance
        run('847',f'{n} {len(edges)}\n'+'\n'.join(f'{a} {b}' for a,b in edges),ans)
    samples=[(3,5,7),(0,0,1),(2147483646,100,2147483647),(-3,5,7)]+[(rng.randint(-10**12,10**12),rng.randrange(10000),rng.randint(1,2147483647)) for _ in range(100)]
    for a,k,p in samples:run('875',f'1\n{a} {k} {p}',pow(a,k,p))
    for _ in range(50):
        n=rng.randrange(9);cap=rng.randrange(15);items=[(rng.randint(1,8),rng.randint(-3,15)) for _ in range(n)]
        best=0
        for mask in range(1<<n):
            weight=sum(v for i,(v,w) in enumerate(items) if mask>>i&1)
            value=sum(w for i,(v,w) in enumerate(items) if mask>>i&1)
            if weight<=cap:best=max(best,value)
        run('002',f'{n} {cap}\n'+'\n'.join(f'{v} {w}' for v,w in items),best)
    for _ in range(50):
        n=rng.randrange(12);a=[rng.randint(-4,4) for _ in range(n)];best=0
        for mask in range(1<<n):
            seq=[x for i,x in enumerate(a) if mask>>i&1]
            if all(x<y for x,y in zip(seq,seq[1:])):best=max(best,len(seq))
        run('895',f'{n}\n'+' '.join(map(str,a)),best)
    run('905','2\n-2000000000 -2000000000\n-2000000000 0',1)
    for _ in range(40):
        intervals=[tuple(sorted((rng.randint(-3,3),rng.randint(-3,3)))) for j in range(rng.randrange(7))]
        points=sorted({x for l,r in intervals for x in (l,r)});best=len(points)
        for count in range(len(points)+1):
            if any(all(any(l<=p<=r for p in choice) for l,r in intervals) for choice in itertools.combinations(points,count)):
                best=count;break
        run('905',f'{len(intervals)}\n'+'\n'.join(f'{l} {r}' for l,r in intervals),best)
    version=subprocess.run([compiler,'--version'],capture_output=True,text=True,check=True).stdout.splitlines()[0]
    result={'compiler':version,'standard':'C++17','seed':20261012,'programs':counts,'total_cases':sum(counts.values()),'result':'PASS','online_judge':'not run'}
    (ROOT/'算法学习手册/程序测试结果.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    print(json.dumps(result,ensure_ascii=False))
if __name__=='__main__':verify()
