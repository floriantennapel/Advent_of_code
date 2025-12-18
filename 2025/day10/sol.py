from queue import Queue
from sys import stdin
import sympy as sp
from itertools import product
from tqdm import tqdm

def button_int(button):
    res = 0
    for b in button:
        res |= (1 << b)
    return res

def diag_int(diag):
    res = 0
    for i, c in enumerate(diag):
        if c == '#':
            res |= (1 << i)
    return res

def int_but(num):
    res = []
    for p in range(32):
        if num & (1<<p) != 0:
            res.append(p)
    return res

def _p1(target, buttons):
    visited = set()
    q = Queue()
    q.put((0, 0))

    while not q.empty():
        cur, count = q.get() 
        if cur in visited:
            continue
        visited.add(cur)
        if cur == target:
            return count  
        for b in buttons:
            q.put((cur^b, count+1))
    return -1

def _p2(buttons, jolts):
    max_range = max(jolts)
    m = len(jolts)
    n = len(buttons)
    A = sp.zeros(m, n)
    for i, b in enumerate(buttons):
        for j in b:
            A[j, i] = 1

    b = sp.Matrix(jolts)
    sol = list(sp.linsolve((A, b)))[0]
    syms = set()
    for s in sol:
        for sym in s.free_symbols:
            syms.add(sym)
    syms = list(syms)

    res = sum(sol)
    if len(syms) == 0:
        return int(res)

    # too lazy to think of a smart way to do this, 
    # brute forcing the rest should work
    lo = 1<<31
    for p in product(range(max_range+1), repeat=len(syms)):
        interp = dict(zip(syms, p)) 
        subs_sum = 0
        for s in sol:
            res = s.subs(interp)
            if res < 0 or not res.is_integer:
                break
            subs_sum += res
        else:
            lo = min(lo, int(subs_sum)) #TODO
    return lo

p1 = 0
p2 = 0
lines = stdin.readlines()
for line in tqdm(lines):
    splitted = line.strip().split()
    target = diag_int(splitted[0][1:-1])
    buttons = []
    for s in splitted[1:]:
        if s[0] == '{':
            break
        t = eval(s)
        if isinstance(t, int):
            t = (t,)
        buttons.append(t)
    jolts = eval(splitted[-1].replace('{','[').replace('}',']'))
    p1 += _p1(target, [button_int(b) for b in buttons]) 
    res = _p2(buttons, jolts)
    p2 += res

print(f'part 1: {p1}')
print(f'part 2: {p2}')
