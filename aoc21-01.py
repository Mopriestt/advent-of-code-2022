import re
from copy import deepcopy

def hasLetter(s):
    return any(c.isalpha() for c in s)

values = { l.split(':')[0] : l.split(':')[1] for l in open('21.in').read().replace(' ', '').split('\n') }

def calc(values):
    while hasLetter(values['root']):
        for key, value in values.items():
            if hasLetter(value):
                names = re.findall(r'\b\w+\b', value)
                for name in names:
                    if hasLetter(name):
                        value = value.replace(name, '(' + values[name] + ')')
                if not hasLetter(value): value = str(eval(value))
                values[key] = value
            else:
                values[key] = str(eval(value))

def check(x, target1, target2):
    d = deepcopy(values)
    d['humn'] = str(x)
    calc(d)
    return eval(d[target1] + '-' + d[target2])

t1, t2 = values['root'].split('+')
r = 100000000000000
l = -r
while r > l:
    mid = l + r >> 1
    res = check(mid, t1, t2)
    print(l, ' ', r, ' ', res)
    if res == 0:
        l = r = mid
        break
    if res < 0: r = mid - 1
    else: l = mid + 1

print(l)