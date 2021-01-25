import string, sys

def cleanup(cs):
    cs = cs.lower()
    xs = []
    for c in cs:
        if c in string.ascii_lowercase:
            xs.append(c)

    return ''.join(xs)

print(cleanup("Hello, world!"))

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

print("test .... ")
print(to_chrs([0, 1, 2, 3, 4, 5]))
print(to_ints(['a', 'c', 'e', 'z'])) 

#################################################################
# Q1: The goal is to count the number of solutions in
#        Z mod 135246, where Z is integers
# to the following equation:
#        x^3 + 425x^2 + 79x + 42 = (congruent to) 0 (mod 135246)
#################################################################

def q_01():
    modrange = 135246
    for i in range(0, modrange + 1):
        if ((i ** 3 + 425 * i ** 2 + 79 * i + 42) % modrange) == 0:
            print("solution found with i = %d" % i)
    
q_01()
