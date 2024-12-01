from sys import stdin

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
counter = {}
for d in l2:
    counter[d] = counter.get(d, 0) + 1
print(sum(a*counter.get(a, 0) for a in l1))
