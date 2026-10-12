from pathlib import Path
import hashlib, json, re, shutil, zipfile
import xml.etree.ElementTree as ET
from handbook_data import CHAPTERS, SUPPLEMENTS

ROOT = Path(__file__).resolve().parent
OUT = ROOT / '算法学习手册'
def write(p, text):
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(text, encoding='utf-8', newline='\n')
def source_text(name):
    return (ROOT / '原始资料' / name).read_text(encoding='utf-8-sig')
def render_entry(title, fields, raw=None, source=None, line=None, ids=(), anchor='', code_link=None):
    if len(fields) != 6: raise ValueError((title, fields))
    idea, walk, proof, cost, caution, example = fields
    s = f'<a id="{anchor}"></a>\n\n## {title}\n\n'
    if source: s += f'来源：`{source}` 第 {line} 行起。以下原文未改写，修正建议单独列出。\n\n'
    else: s += '类型：题目清单衍生的补充讲解，原文件未提供此专题代码。\n\n'
    if ids: s += '练习题号：' + '、'.join('AcWing '+x for x in ids) + '。题号来自本地资料，未声称通过在线评测。\n\n'
    for label, value in [('知识点与用途',idea),('代码与步骤解读',walk),('为什么正确',proof),('复杂度',cost),('使用条件与易错点',caution),('小例子',example)]:
        s += f'### {label}\n\n{value}。\n\n'
    if raw:
        s += f'### 原始模板与公式\n\n以下为教学片段，可能包含伪代码、缺少的全局变量或原文笔误，不能整段直接编译。\n\n```text\n{raw.strip()}\n```\n\n'
        if code_link: s += f'[独立原文片段]({code_link})\n\n'
    return s

def build():
    manifest=[]; contents=[]; chapters=[]
    for filename, chapter, data in CHAPTERS:
        text=source_text(filename).split('作者：yxc')[0].rstrip()
        lines=text.splitlines()
        starts=[i for i,l in enumerate(lines) if '——' in l or l in ('树与图的存储','树与图的遍历','C++ STL简介')]
        rows=[l.split('|') for l in data.strip().splitlines()]
        if len(starts)!=len(rows): raise ValueError((filename,len(starts),len(rows)))
        entries=[]; toc=[]
        for n,(start, fields) in enumerate(zip(starts,rows),1):
            end=starts[n] if n<len(starts) else len(lines)
            header=lines[start]; title=re.sub(r'^\(\d\)\s*','',header.split('——')[0].strip())
            ids=re.findall(r'AcWing\s+(\d+)',header,re.I)
            raw='\n'.join(lines[start+1:end]).strip()
            slug=f'{chapter[:2]}-{n:02d}'
            fragment=f'{slug}-{title}.txt'
            write(OUT/'原文片段'/chapter/fragment,raw+'\n')
            code_link='../原文片段/'+chapter+'/'+fragment
            entries.append(render_entry(title,fields,raw,filename,start+1,ids,slug,code_link))
            toc.append(f'- [{title}](#{slug})')
            manifest.append({'chapter':chapter,'title':title,'anchor':slug,'source':filename,'line':start+1,'ids':ids,'fragment':str(Path('算法学习手册')/'原文片段'/chapter/fragment).replace('\\','/')})
        body=f'# {chapter[3:]}\n\n[返回项目首页](../../README.md) · [来源与修正](../来源与修正.md)\n\n'+ '\n'.join(toc)+'\n\n'+'\n'.join(entries)
        write(OUT/'章节'/(chapter+'.md'),body)
        contents.append((chapter, entries))
        chapters.append(f'- [{chapter[3:]}](章节/{chapter}.md)：{len(entries)} 个原文条目')
    for chapter,data in SUPPLEMENTS.items():
        entries=[]; toc=[]
        for n,row in enumerate(data.strip().splitlines(),1):
            title, ids, idea, walk, cost, caution, example=row.split('|')
            slug=f'{chapter[:2]}-{n:02d}'
            proof={'05-动态规划':'定义状态后按依赖顺序计算，转移枚举全部合法的最后一步或选择；同一状态保留最优值或累计方案数', '06-贪心':'必须用交换论证或覆盖界证明当前选择可属于某个最优解；仅局部看起来最好不能作为证明'}[chapter]
            if chapter=='06-贪心': proof += '。本条的关键是'+caution
            entries.append(render_entry(title,[idea,walk,proof,cost,caution,example],ids=ids.split(','),anchor=slug))
            toc.append(f'- [{title}](#{slug})')
            manifest.append({'chapter':chapter,'title':title,'anchor':slug,'source':'基础课题目.docx','ids':ids.split(','),'supplement':True})
        write(OUT/'章节'/(chapter+'.md'),f'# {chapter[3:]}（补充）\n\n[返回项目首页](../../README.md)\n\n'+ '\n'.join(toc)+'\n\n'+'\n'.join(entries))
        contents.append((chapter,entries)); chapters.append(f'- [{chapter[3:]}](章节/{chapter}.md)：{len(entries)} 个补充专题')
    # 单文件总手册的原文片段路径与章节相差一级。
    all_text='# 算法学习手册\n\n'+ '\n'.join(chapters)+'\n\n'
    all_text += '\n'.join(f'- [{x["title"]}](#{x["anchor"]})' for x in manifest)+'\n\n'
    for chapter,entries in contents:
        all_text+=f'# {chapter[3:]}\n\n'+'\n'.join(entries).replace('(../原文片段/','(原文片段/')
    write(OUT/'算法学习手册.md',all_text)
    write(ROOT/'manifest.json',json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
    z=zipfile.ZipFile(ROOT/'原始资料'/'基础课题目.docx')
    tree=ET.fromstring(z.read('word/document.xml')); ns={'w':'http://schemas.openxmlformats.org/wordprocessingml/2006/main'}
    paras=[''.join(t.itertext()) for t in tree.findall('.//w:p',ns)]
    paragraphs='\n'.join(paras)
    write(OUT/'题目清单原文.txt',paragraphs+'\n')
    # 保留原文主题归属及出现顺序，去掉历史打卡人数。
    problem_rows=[]; group=''; topic=''
    for p in paras:
        p=p.strip()
        if re.match('第.+讲',p): group=p.split('完成情况')[0].strip()
        elif re.search(r'AcWing\s+\d+\.',p):
            for number in re.findall(r'AcWing\s+(\d+)\.',p): problem_rows.append((number,group,topic))
        elif p and '打卡' not in p and not p.startswith('包括') and p!='OK': topic=p
    idx='# 基础课题目索引\n\n来源：`基础课题目.docx`。原文只有题号、分类和历史打卡人数，没有题面或解答；本表不把人数当作难度或完成情况。\n\n'
    idx+='| 题号 | 原分类 | 专题 | 对应讲解 |\n|---|---|---|---|\n'
    for number,group,topic in problem_rows:
        refs=[f'[{x["title"]}](章节/{x["chapter"]}.md#{x["anchor"]})' for x in manifest if number in x['ids']]
        idx+=f'| AcWing {number} | {group} | {topic} | '+('、'.join(refs) if refs else '见[清单专有题目补充](清单专有题目补充.md)')+' |\n'
    write(OUT/'题目索引.md',idx)
    write(ROOT/'题目索引数据.json',json.dumps(problem_rows,ensure_ascii=False,indent=2)+'\n')
    print(f'Generated {len(manifest)} entries; {len(problem_rows)} problem records')
if __name__=='__main__': build()
