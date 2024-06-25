def part1_valid(passw: tuple[int, int, str, str]) -> bool:
    return passw[0] <= passw[3].count(passw[2]) <= passw[1]


def part2_valid(passw: tuple[int, int, str, str]) -> bool:
    sum = 0
    for i in range(2):
        if passw[3][passw[i] - 1] == passw[2]:
            sum += 1
    
    return sum == 1


def parse_line(line: str) -> tuple[int, int, str, str]:
    splitted = line.strip().split()
    a, b = (int(n) for n in splitted[0].split('-'))
    return (a, b, splitted[1][0], splitted[2])


def main():
    filename = 'in.txt'
    with open(filename) as file:
        passwords = [parse_line(line) for line in file]
    
    print('part 1:', sum([1 if part1_valid(passw) else 0 for passw in passwords]))
    print('part 2:', sum([1 if part2_valid(passw) else 0 for passw in passwords]))


if __name__ == '__main__':
    main()