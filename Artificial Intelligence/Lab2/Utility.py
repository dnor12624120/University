def filter_zeros(l):
    copy = l[:]
    while 0 in copy:
        copy.remove(0)
    return copy

def generate_empty_list(n):
    return [0] * n