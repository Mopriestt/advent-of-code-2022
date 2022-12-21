def hasLetter(s):
    return any(c.isalpha() for c in s)

values = { l.split(':')[0] : l.split(':')[1].strip().replace('/', '//') for l in open('21.in').read().strip().split('\n') }

while hasLetter(values['root']):
    for key, value in values.items():
        if hasLetter(value):
            for k, v in values.items():
                if not hasLetter(v):
                    value = value.replace(k, v)
            if not hasLetter(value): value = str(eval(value))
            values[key] = value
        else:
            values[key] = str(eval(value))
print(eval(values['root']))
