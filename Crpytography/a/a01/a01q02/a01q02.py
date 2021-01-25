def q_02():
    modrange = 135246
    num_sols = 0
    for i in range(0, modrange + 1):
        if ((i ** 3 + 425 * i ** 2 + i + 42) % modrange) == 0:
            num_sols += 1

    return num_sols

if __name__ == '__main__':
    print(q_02())
