import re

def hasLetter(s):
    return any(c.isalpha() for c in s)

values = { l.split(':')[0] : l.split(':')[1] for l in open('21.in').read().replace(' ', '').split('\n') }

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
print(eval(values['root']))
