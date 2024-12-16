from sys import stdin
from heapq import heappush, heappop

dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

best = set()
def bt(elem):
    best.add(elem[1])
    if len(elem[3]) == 0:
        return
    for e in elem[3]:
        bt(e)

grid = [[c for c in line.strip()] for line in stdin if line != '\n']
grid[-2][1] = '.'
grid[1][-2] = '.'

target = (1, len(grid[0])-2)
q = [(0, (len(grid)-2, 1), 0, [])]
visited = {}

while(len(q) > 0):
    current = heappop(q)
    dist, pos, dir, preds = current
    
    if (pos == target):
        print(dist)
        bt(current)
        break

    if (pos, dir) in visited:
        if dist == visited[(pos, dir)][0]:
            visited[(pos, dir)][1].append(current)

        continue
    visited[(pos, dir)] = (dist, preds)

    dr, dc = dirs[dir]
    r, c = pos[0]+dr, pos[1]+dc
    if (grid[r][c] != '#'):
        heappush(q, (dist+1, (r, c), dir, [current]))
    
    for i in range(dir-1, dir+2, 2):
        heappush(q, (dist+1000, pos, i%4, [current]))

print(len(best))
