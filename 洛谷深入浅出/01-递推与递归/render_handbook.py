from pathlib import Path
import re
import markdown
p = Path(__file__).resolve().parent
source = (p / '学习手册.md').read_text(encoding='utf-8')
knowledge = (p / '知识点全解.md').read_text(encoding='utf-8-sig')
source = re.sub(r'# 知识点全解：先理解，再套题.*?(?=# 对照图片：六个经典例题)', lambda _: knowledge+'\n', source, count=1, flags=re.S)
# Keep the supplied note and the generated chapter contents synchronized.
note = (p / '带括号的递归解析.md').read_text(encoding='utf-8-sig')
source = re.sub(r'# 带括号的递归解析（递归 \+ 全局下标）.*?(?=## 如何安排学习)', lambda _: note+'\n', source, count=1, flags=re.S)
source = re.sub(r'<!-- TOC START -->.*?<!-- TOC END -->\n*', '', source, flags=re.S)
source = re.sub(r'<a id="section-\d+"></a>\n', '', source)
lines = source.splitlines()
anchored = []
entries = []
in_code = False
for line in lines:
    if line.startswith('```'):
        in_code = not in_code
    match = None if in_code else re.match(r'^(#{1,2}) (.+)$', line)
    if match:
        level, title = len(match[1]), match[2]
        ident = f'section-{len(entries)+1}'
        entries.append((level, title, ident))
        anchored.append(f'<a id="{ident}"></a>')
    anchored.append(line)
toc = '<!-- TOC START -->\n## 目录\n\n'
for level, title, ident in entries[1:]:
    toc += '' + f'- [{title}](#{ident})\n'
toc += '\n<!-- TOC END -->\n\n'
source = '\n'.join(anchored)+'\n'
first_break = source.find('\n', source.find('# '))
source = source[:first_break+1]+'\n'+toc+source[first_break+1:]
(p / '学习手册.md').write_text(source, encoding='utf-8', newline='\n')
body = markdown.markdown(source, extensions=['fenced_code', 'tables', 'sane_lists'])
headings = []
def anchor(match):
    number = len(headings) + 1
    headings.append((number, match.group(2)))
    return f'<h{match.group(1)} id="s{number}">{match.group(2)}</h{match.group(1)}>'
body = re.sub(r'<h([12])>(.*?)</h\1>', anchor, body)
body = body.replace('<table>', '<div class="table-wrap"><table>').replace('</table>', '</table></div>')
nav = ''.join(f'<a href="#s{i}">{title}</a>' for i, title in headings)
page = (p / 'index.html').read_text(encoding='utf-8')
page = re.sub(r'<nav>.*?</nav>', lambda _: '<nav>'+nav+'</nav>', page, count=1, flags=re.S)
page = re.sub(r'<article>.*?</article>', lambda _: '<article>'+body+'</article>', page, count=1, flags=re.S)
(p / 'index.html').write_text(page, encoding='utf-8', newline='\n')
print(f'Rendered {len(headings)} navigation entries')
