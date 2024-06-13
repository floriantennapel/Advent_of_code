from heapq import heappush, heappop

dirs = [(0, -1), (1, 0), (0, 1), (-1, 0)]


def opposite(a, b):
    x1, y1 = a
    x2, y2 = b
    return (x1 == x2 and y1 != y2) or (y1 == y2 and x1 != x2)


def add(a, b):
    return (a[0] + b[0], a[1] + b[1])


def is_valid(pos, city):
    x, y = pos
    return x >= 0 and x < len(city[0]) and y >= 0 and y < len(city)


def dijkstra(city, min_steps, max_steps):
    pq = [(0, ((1, 0), 0, (0, 0))), (0, ((0, 1), 0, (0, 0)))]
    visited = set()

    while len(pq) != 0:
        cost, crucible = heappop(pq)
        if crucible in visited:
            continue
        visited.add(crucible)

        dir, steps, pos = crucible
        if pos == (len(city[0]) - 1, len(city) - 1):
            return cost

        for d in dirs:
            if opposite(dir, d):
                continue
            elif d == dir:
                if steps == max_steps:
                    continue
                else:
                    next_steps = steps + 1
            else:
                if steps < min_steps:
                    continue
                else:
                    next_steps = 1

            next_pos = add(pos, d)
            if is_valid(next_pos, city):
                heappush(pq, (cost + city[next_pos[1]][next_pos[0]], (d, next_steps, next_pos)))


if __name__ == '__main__':
    file_name = 'in'
    file = open(file_name)
    city = [[int(c) for c in line.strip()] for line in file]

    print('part 1:', dijkstra(city, 0, 3))
    print('part 2:', dijkstra(city, 4, 10))
