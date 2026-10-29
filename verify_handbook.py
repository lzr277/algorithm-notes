from pathlib import Path
import hashlib, json, re, subprocess, sys
from urllib.parse import unquote
ROOT=Path(__file__).resolve().parent
def check():
    manifest=json.loads((ROOT/'manifest.json').read_text(encoding='utf-8'))
    assert len(manifest)==86
    assert sum(not x.get('supplement',False) for x in manifest)==63
    rows=json.loads((ROOT/'题目索引数据.json').read_text(encoding='utf-8'))
    assert len(rows)==104 and len({r[0] for r in rows})==104
    extra=(ROOT/'算法学习手册/清单专有题目补充.md').read_text(encoding='utf-8')
    covered={i for x in manifest for i in x['ids']}|set(re.findall(r'## AcWing (\d+)',extra))
    assert all(r[0] in covered for r in rows), 'Some problems lack explanations'
    for x in manifest:
        chapter=ROOT/'算法学习手册/章节'/(x['chapter']+'.md')
        assert f'id="{x["anchor"]}"' in chapter.read_text(encoding='utf-8')
        if 'fragment' in x: assert (ROOT/x['fragment']).exists()
    checked=0
    for p in ROOT.rglob('*.md'):
        text=p.read_text(encoding='utf-8')
        # C++ lambda 的 ](...) 不是 Markdown 链接；跳过围栏代码块。
        text=re.sub(r'^```[^\n]*\n.*?^```\s*$', '', text, flags=re.M|re.S)
        for link in re.findall(r'\]\(([^)]+)\)',text):
            if link.startswith(('http:','https:','mailto:')):continue
            target,_,anchor=link.partition('#')
            path=p.parent/unquote(target) if target else p
            assert path.exists(),f'{p.name}: missing {link}'
            if anchor and path.suffix=='.md':
                assert f'id="{anchor}"' in path.read_text(encoding='utf-8'),f'bad anchor {link}'
            checked+=1
    generated=[ROOT/'manifest.json',ROOT/'题目索引数据.json']+list((ROOT/'算法学习手册/章节').glob('*.md'))+list((ROOT/'算法学习手册/原文片段').rglob('*.txt'))+[ROOT/'算法学习手册/算法学习手册.md',ROOT/'算法学习手册/题目索引.md',ROOT/'算法学习手册/题目清单原文.txt']
    before={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in generated}
    subprocess.run([sys.executable,str(ROOT/'build_handbook.py')],check=True,cwd=ROOT)
    assert before=={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in generated},'Generation is not deterministic'
    print(f'PASS: 86 entries, 104 problems, {checked} local links; deterministic generation')
if __name__=='__main__':check()
