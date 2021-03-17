import string

def to_int(c):
    if not isinstance(c, str): raise ValueError("%s is not str" % c)
    if len(c) != 1: raise ValueError("length of %s is not 1" % c)
    if not('a' <= c <= 'z'): raise ValueError("char %s is not in a..z" % c)

    return ord(c) - ord('a')

def to_chr(i):
    if not isinstance(i, int): raise ValueError("%s is not int" % i)
    if i < 0 or i > 25: raise ValueError("%s is not in 0..25" % i)
    return chr(i + ord('a'))

def to_ints(cs):
    ints = []
    for c in cs:
        ints.append(to_int(c))

    return ints

def to_chrs(xs):
    chrs = []
    for x in xs:
        chrs.append(to_chr(x))

    return chrs

def cleanup(s):
    cs = s.lower()
    xs = []
    for c in cs:
        if c in string.ascii_lowercase:
            xs.append(c)

    return ''.join(xs)

def Shift_E(k, s):
    new_str = []
    for val in s:
        new_char = to_chr((to_int(val) + k) % 26)
        new_str.append(new_char)

    return ''.join(new_str)

k = int(input())
m = input()

print(Shift_E(k, cleanup(m)))
