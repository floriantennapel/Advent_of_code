from sys import stdin
from collections import Counter
from math import prod

boxes = [list(map(int, l.split(','))) for l in stdin]
dists = []
for i, (x1, y1, z1) in enumerate(boxes):
    for j, (x2, y2, z2) in enumerate(boxes[i+1:]):
        dist = ((x1-x2)**2 + (y1-y2)**2 + (z1-z2)**2)**0.5
        dists.append((dist, i, j+i+1))
dists.sort()

circuits = [i for i, _ in enumerate(boxes)]
def root(b):
    count = 0
    while circuits[b] != b:
        count += 1
        b = circuits[b]
    return b

n_shortest = 1000
for _, a, b in dists[:n_shortest]: 
    circuits[root(a)] = root(b)
    # very small input, so path compression not needed

counts = Counter(map(root, circuits))
p1 = prod(sorted(counts.values())[-3:])
print(f'part 1: {p1}')

# input so small that ineffiecient algorithm doesn't matter
la, lb = -1, -1
for _, a, b in dists[n_shortest:]:
    ra, rb = root(a), root(b)
    if ra != rb:
        la, lb = a, b
        circuits[ra] = rb
    
print(f'part 2: {boxes[la][0]*boxes[lb][0]}')



