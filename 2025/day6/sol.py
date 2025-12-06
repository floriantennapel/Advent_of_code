from sys import stdin

def add_mul(a, b, op):
    if op == '+':
        return a + b
    else:
        return a * b

grid = [[c for c in l.strip('\n')] for l in stdin]

p1_nums = [list(map(int, ''.join(l).split())) for l in grid[:-1]]
ops = [(j, op) for j, op in enumerate(grid[-1]) if op != ' ']

p1 = 0
for j, (_, op) in enumerate(ops):
    total = p1_nums[0][j]
    for l in p1_nums[1:]:
        total = add_mul(total, l[j], op)
    p1 += total
print(f'part 1: {p1}')

def ceph_math(j):
    op = grid[-1][j]
    total = 0 if op == '+' else 1
    while j < len(grid[0]):
        num = 0
        for row in grid[:-1]:
            if row[j] != ' ':
                num = num * 10 + int(row[j])
        if num == 0:
            break
        total = add_mul(total, num, op)
        j += 1
    return total

p2 = sum(ceph_math(j) for j, _ in ops)
print(f'part 2: {p2}')
