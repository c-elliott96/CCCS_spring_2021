def q_01:
    modrange = 135246
    for i in range(0, modrange + 1):
        num_sols = 0
        if ((i ** 3 + 425 * i ** 2 + 79 * i + 42) % modrange) == 0:
            num_sols += 1

    return num_sols
