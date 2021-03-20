def inv(a, n):
    for i in range(1, n):
        if (i * a) % n == 1:
            return i

    return None

a = int(input())
n = int(input())
print(inv(a, n))

