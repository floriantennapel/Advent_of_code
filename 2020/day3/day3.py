def parse_input(filename: str) -> list[list[bool]]:
    with open(filename) as file:
        return [[c == '#' for c in line] for line in file.read().splitlines()]


def count_trees(tree_map: list[list[bool]], dr: int, dc: int) -> int:
    r, c = 0, 0
    counter = 0

    while r < len(tree_map):
        counter += 1 if tree_map[r][c] else 0
        r += dr
        c = (c + dc) % len(tree_map[0])
    
    return counter


def part1(tree_map: list[list[bool]]) -> int:
    return count_trees(tree_map, 1, 3)


def part2(tree_map: list[list[bool]]) -> int:
    prod = 1
    for dc, dr in [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]:
        prod *= count_trees(tree_map, dr, dc)
    
    return prod

def main():
    tree_map = parse_input('in.txt')

    print('part 1:', part1(tree_map))
    print('part 2:', part2(tree_map))

if __name__ == '__main__':
    main()