from pathlib import Path
import re
import markdown
p = Path(__file__).resolve().parent
source = (p / '学习手册.md').read_text(encoding='utf-8')
knowledge = (p / '知识点全解.md').read_text(encoding='utf-8-sig')
source = re.sub(r'# 知识点全解：先理解，再套题.*?(?=# 对照图片：六个经典例题)', lambda _: knowledge+'\n', source, count=1, flags=re.S)
(p / '学习手册.md').write_text(source, encoding='utf-8')
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
(p / 'index.html').write_text(page, encoding='utf-8')
print(f'Rendered {len(headings)} navigation entries')
