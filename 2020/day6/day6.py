def parse_input(filename: str) -> list[list[set]]:
    retlist = []

    with open(filename) as file:
        group = []
        for line in file:
            if line.isspace():
                retlist.append(group)
                group = []
            else:
                group.append(line.strip())
    retlist.append(group)
    
    return retlist


def part1(groups: list[list[str]]) -> int:
    return sum([len(set(''.join(group))) for group in groups])


def part2(groups: list[list[str]]) -> int:
    return sum(len(set.intersection(*[set(p) for p in g])) for g in groups)


def main():
    groups = parse_input('in.txt')

    print('part 1:', part1(groups))
    print('part 2:', part2(groups))


if __name__ == '__main__':
    main()



