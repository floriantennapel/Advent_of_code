from sys import stdin

intervals = []
for line in stdin:
    line = line.strip()
    if line == '':
        break
    intervals.append(tuple(map(int, line.split('-'))))
intervals.sort()

ids = sorted(list(map(int, stdin)))

p1 = 0
interval_ind = 0
lo, hi = intervals[0]
i = 0
while i < len(ids):
    ident = ids[i]
    if ident < lo:
        i += 1
    elif ident <= hi:
        p1 += 1
        i += 1
    else:
        interval_ind += 1
        if interval_ind >= len(intervals):
            break
        lo, hi = intervals[interval_ind]
print(f'part 1: {p1}')

lo, hi = -1,-1 
p2 = 0
for a, b in intervals:
    if b <= hi:
        continue
    lo = max(hi+1, a)
    hi = b 
    p2 += hi - lo + 1
print(f'part 2: {p2}')
