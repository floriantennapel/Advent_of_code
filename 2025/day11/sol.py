from sys import stdin
from functools import cache

graph = {f: t.strip().split() for f, t in (l.split(': ') for l in stdin)} 

@cache
def solve(node):
    if node == 'out':
        return (1, 0, 0)
    res = tuple(map(sum, zip(*map(solve, graph[node]))))
    if node == 'fft' or node == 'dac':
        res = (res[0], res[0], res[1])
    return res

print(f'part 1: {solve("you")[0]}')
print(f'part 2: {solve("svr")[2]}')
