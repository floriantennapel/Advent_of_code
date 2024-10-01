lo = 246515
hi = 739105

def has_two_adj(str_num):
    prev = str_num[0]
    for c in str_num[1:]:
        if c == prev:
            return True
        prev = c

    return False

def nondecreasing(str_num):
    prev = ord(str_num[0])
    for c in str_num[1:]:
        if ord(c) < prev:
            return False
        prev = ord(c)

    return True

def has_two_adj_p2(str_num):
    prev = str_num[0]
    count = 1
    for c in str_num[1:]:
        if c == prev:
            count += 1
        else:
            if count == 2:
                return True
            count = 1
        prev = c
    if count == 2:
        return True
    
    return False

def is_valid_p1(num):
    as_str = str(num)
    if has_two_adj(as_str) and nondecreasing(as_str):
        return True
    return False

def is_valid_p2(num):
    as_str = str(num)
    if has_two_adj_p2(as_str) and nondecreasing(as_str):
        return True
    return False

print(len([n for n in range(lo, hi+1) if is_valid_p1(n)]))
print(len([n for n in range(lo, hi+1) if is_valid_p2(n)]))
