from pathlib import Path
import re
import markdown
p=Path(__file__).resolve().parent
s=(p/'学习手册.md').read_text(encoding='utf-8')
s=re.sub(r'<!--TOC-->.*?<!--/TOC-->\n*','',s,flags=re.S)
s=re.sub(r'<a id="c\d+"></a>\n','',s)
entries=[];lines=[];fence=False
for line in s.splitlines():
    if line.startswith('```'):fence=not fence
    if not fence and re.match(r'^#{1,2} ',line):
        ident='c'+str(len(entries));title=line.split(' ',1)[1]
        entries.append((ident,title));lines.append(f'<a id="{ident}"></a>')
    lines.append(line)
s='\n'.join(lines)+'\n';pos=s.find('\n',s.find('# '))+1
toc='\n<!--TOC-->\n## 目录\n\n'+''.join(f'- [{t}](#{i})\n' for i,t in entries[1:])+'\n<!--/TOC-->\n\n'
s=s[:pos]+toc+s[pos:]
(p/'学习手册.md').write_text(s,encoding='utf-8',newline='\n')
body=markdown.markdown(s,extensions=['fenced_code','tables','sane_lists']).replace('<h2>目录</h2>','<h2 id="book-toc">目录</h2>').replace('<h2>目录</h2>','<h2 id="book-toc">目录</h2>')
page=(p/'index.html').read_text(encoding='utf-8')
page=re.sub(r'<article>.*?</article>',lambda _: '<article>'+body+'</article>',page,flags=re.S)
(p/'index.html').write_text(page,encoding='utf-8',newline='\n')
