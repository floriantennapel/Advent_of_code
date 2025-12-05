from sys import stdin

def jolt(bat, s):
    bat = list(enumerate(bat))
    a = 0
    total = 0
    for i in reversed(range(s)):
        ran = bat[a:-i] if i != 0 else bat[a:]
        ind, biggest = max(ran, key=lambda p: p[1])
        total = total * 10 + biggest
        a = ind+1
    return total

if __name__ == '__main__':
    inp = [list(map(int, line.strip())) for line in stdin]
    print(f'part 1: {sum(jolt(b, 2) for b in inp)}') 
    print(f'part 2: {sum(jolt(b, 12) for b in inp)}')
