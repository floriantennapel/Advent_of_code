def read_input(filename):
    file = open(filename, 'r')
    caves = dict()

    for line in file:
        a, b = line.strip().split('-')
        add_cave(caves, a, b)
        add_cave(caves, b, a)
    
    file.close()
    return caves


def add_cave(caves, from_cave, to_cave):
    if caves.get(from_cave) is None:
        caves[from_cave] = []

    caves[from_cave].append(to_cave)


def is_small_cave(cave):
    return cave not in ['end', 'start'] and cave.islower()


def count_paths(caves, visited, cave, twiceVisit):
    if cave == 'start' and visited.get(cave, 0) != 0:
        return 0
    if cave == 'end':
        return 1
    
    newVisited = dict(visited)
    newVisited[cave] = True
    sum = 0
    for next in caves[cave]:
        if is_small_cave(next) and visited.get(next) is not None:
            if not twiceVisit:
                sum += count_paths(caves, newVisited, next, True)
            continue

        sum += count_paths(caves, newVisited, next, twiceVisit)

    return sum



#=================
# Program start
#=================

filename = "in.txt"
visited = dict()
caves = read_input(filename)

print(f"part1: {count_paths(caves, visited, 'start', True)}")
print(f"part2: {count_paths(caves, visited, 'start', False)}")




