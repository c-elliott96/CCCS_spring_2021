# Author: Christian Elliott
# Date: 1-23-2021
# Crpytography - Assignment 1, Question 4
def inv(a, n):
    for i in range(1, n):
        if a * i % n == 1:
            return i

    return None

MODRANGE = 135246
def q_04(MODRANGE):
    n = inv(27109, MODRANGE)
    c = n * 5316 % MODRANGE
    for x in range(MODRANGE):
        if x ** 3 % MODRANGE == c:
            return c

    return None
    
print(q_04(MODRANGE))

