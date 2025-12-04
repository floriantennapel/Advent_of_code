from sys import stdin

def surrounding(r, c):
    count = 0
    for i in range(max(r-1, 0), min(r+2, len(grid))):
        for j in range(max(c-1, 0), min(c+2, len(grid[0]))):
            if (i, j) == (r, c):
                continue
            if grid[i][j]:
                count += 1
    return count

if __name__ == '__main__':
    grid = [[True if c == '@' else False for c in line.strip()] for line in stdin]

    p1_done = False
    total_count = 0
    while True:
        count = 0
        for i, l in enumerate(grid):
            for j, _ in enumerate(l):
                if grid[i][j] and surrounding(i, j) < 4:
                    count += 1
                    if p1_done:
                        grid[i][j] = False
        if not p1_done:
            print(f'part 1: {count}')
            p1_done = True
        else:
            total_count += count
        if count == 0:
            break

    print(f'part 2: {total_count}')
