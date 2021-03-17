# File: crypto.py
# Author: Christian Elliott

import string, sys

VERBOSITY = 0

def cleanup(cs):
  cs = cs.lower()
  xs = []
  for c in cs: 
    if c in string.ascii_lowercase:
      xs.append(c)

  return ''.join(xs)

def to_int(c):
  if not isinstance(c, str): raise ValueError("%s is not str" % c)
  if len(c) != 1: raise ValueError("length of %s is not 1" % c)
  if not('a' <= c <= 'z'): raise ValueError("char %s not in a..z" % c)
  
  return ord(c) - ord('a')

def to_chr(i):
  if not isinstance(i, int): raise ValueError("%d is not int" % i)
  if i < 0 or i > 25: raise ValueError("int %d not in 0..25" % i)
  
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

# brute force multiplicative inverse of a % n
def inv(a, n):
  for x in range(1, n):
    if VERBOSITY == 1:
      print("inv(%s, %s): testing %s" % (a, n, x))

    if a * x % n == 1:
      if VERBOSITY == 1:
        print("inv(%s, %s): returning %s" % (a, n, x))

      return x

  if VERBOSITY == 1:
    print("inv(%s, %s): returning None" % (a, n))

  return None

def printstr(s, columns=50, omit_int=False):
  print("     ", end='')
  for i in range(columns):
    if i % 10 == 0:
      sys.stdout.write("%s" % (i // 10))
    else:
      sys.stdout.write(" ")
  if not omit_int:
    sys.stdout.write(" ")
    for i in range(columns):
      if i % 10 == 0:
        sys.stdout.write("%3s" % (i // 10))
      else:
        sys.stdout.write("   ")
  print()
  print("     ", end='')
  for i in range(0, columns):
    sys.stdout.write("%s" % (i % 10))
  if not omit_int:
    sys.stdout.write(" ")
    for i in range(0, columns):
      sys.stdout.write("%3s" % (i % 10))
  print()
  def drawline():
    sys.stdout.write("    +" + "-" * columns + "+")
    if not omit_int:
      sys.stdout.write("---" * columns + "+")
    print()
  drawline()
  line = 0
  while s != "":
    t = s[:columns]
    t = t + " " * (columns - len(t)) + "|"
    sys.stdout.write("%4s|%s" % (line, t))
    if not omit_int:
      t = s[:columns]
      t = to_ints(t)
      sys.stdout.write("".join(["%3s" % _ for _ in t]))
      sys.stdout.write("   " * (columns - len(t)))
      sys.stdout.write("|")
    print()
    s = s[columns:]
    line += 1
  drawline()
  

def affine_E(a, b, pt):
  out = ''
  pt_ints = to_ints(pt)
  for val in pt_ints:
    c_val = ((val * a) + b) % 26
    out += to_chr(c_val)
  return out


def affine_D(a, b, ct):
  out = ''
  ct_ints = to_ints(ct)
  a_inv = inv(a, 26)
  for val in ct_ints:
    p_val = (a_inv * (val - b)) % 26
    out += to_chr(p_val)
  return out
  

if __name__ == '__main__':
  print(affine_E(3, 12, 'gollum'))
  print(affine_D(3, 12, 'ecttuw'))
