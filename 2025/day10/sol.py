from queue import Queue
from sys import stdin
import scipy.optimize as opt
import scipy as sp
import numpy as np

def button_int(button):
    res = 0
    for b in button:
        res |= (1 << b)
    return res

def diagram_int(diag):
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
    '''
    As this is a integer linear optimization problem, I am using the scipy.optimize.linprog
    function to solve for optimal coefficients.

    After having watched some lectures on linear programming, I realize it is way too much work to
    implement this from scratch. 
    My original solution found unknown coefficients using gaussian elimination and iterated over all 
    possible values to find a minimum. This was kind of slow and also relied on external libraries.

    If I was unable to use external libraries I would probably write the gaussian elimination algorithm
    from scratch and be a bit smarter about choosing the unknowns.
    '''
    m = len(jolts)
    n = len(buttons)
    A = np.zeros((m,n))
    c = np.ones(n) # minimizing for linear sum of coefficients
    b = np.array(jolts) # setting as both lower and upper bound i.e. equality bound

    for j, but in enumerate(buttons):
        for i in but:
            A[i, j] = 1

    integrality = np.ones_like(c)
    res = opt.linprog(c=c, A_eq=A, b_eq=b, integrality=integrality)
    return int(res.fun)

p1 = 0
p2 = 0
lines = stdin.readlines()
for line in lines:
    splitted = line.strip().split()
    target = diagram_int(splitted[0][1:-1])
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
