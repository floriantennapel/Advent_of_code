from queue import PriorityQueue


def read_input(filename: str):
    file = open(filename, 'r')

    ret_list = [[int(c) for c in line.strip()] for line in file]
    file.close()

    return ret_list


def get_next(cavern, pos, part2):
    next = set()

    r = pos[0]
    c = pos[1]
    maxRow = len(cavern) - 1
    maxCol = len(cavern[0]) - 1

    if (part2):
        maxRow = (maxRow + 1) * 5 - 1
        maxCol = (maxCol + 1) * 5 - 1

    if (r != 0):
        next.add((r-1, c))
    if (r != maxRow):
        next.add((r+1, c))
    if (c != 0):
        next.add((r, c-1))
    if (c != maxCol):
        next.add((r, c+1))


    return next


def get_risk(cavern, pos):
    rows = len(cavern)
    cols = len(cavern[0])

    rel_row = pos[0] % rows
    rel_col = pos[1] % cols
    added_cost = int(pos[0] / rows) + int(pos[1] / cols)

    return (cavern[rel_row][rel_col] + added_cost - 1) % 9 + 1


def dijkstra(cavern, part2=False):
    start = (0, 0)
    end = (len(cavern) - 1, len(cavern[0]) - 1)
    if part2:
        end = ((end[0] + 1) * 5 - 1, (end[1] + 1) * 5 - 1)

    visited = {start}
    queue = PriorityQueue()
    queue.put((0, start))

    while not queue.empty():
        current = queue.get()
        if current[1] == end:
            return current[0]

        next = get_next(cavern, current[1], part2)
        for nextPos in next:
            if nextPos in visited:
                continue
            visited.add(nextPos)
            queue.put((get_risk(cavern, nextPos) + current[0], nextPos))


#================
# program start
#================

filename = 'in.txt'
cavern = read_input(filename)
print('part1:', dijkstra(cavern))
print('part1:', dijkstra(cavern, part2=True))
