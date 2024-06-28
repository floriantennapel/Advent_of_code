import math

def part1(timestamp: int, buses: list[str]) -> int:
    only_valid = [int(b) for b in buses if b.isdigit()]
    departure, id = min([((timestamp // id + 1) * id, id) for id in only_valid])
    return id * (departure - timestamp)


def part2(buses: list[str]) -> int:
    only_valid = [(int(b), i) for i, b in enumerate(buses) if b.isdigit()]
    included_buses = [only_valid[0][0]]
    s = 0

    while len(included_buses) < len(only_valid):
        s += math.prod(included_buses)

        for b, i in only_valid[len(included_buses):]:
            if (s + i) % b == 0:
                included_buses.append(b)
            else:
                break

    return s


def main():
    with open('in.txt') as file:
        timestamp = int(file.readline())
        buses = file.readline().split(',')

    print('part 1:', part1(timestamp, buses))
    print('part 2:', part2(buses))


if __name__ == '__main__':
    main()

