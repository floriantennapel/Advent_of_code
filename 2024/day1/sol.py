from sys import stdin
from collections import Counter

l1 = []
l2 = []
for l in stdin:
    a, b = (int(d) for d in l.split())
    l1.append(a)
    l2.append(b)

# part 1
l1.sort()
l2.sort()
print(sum(abs(a-b) for a, b in zip(l1, l2)))

# part 2
counter = Counter(l2)
print(sum(a*counter[a] for a in l1))
