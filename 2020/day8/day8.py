def parse_input(filename: str) -> list[tuple[str, str]]:
    with open(filename) as file:
        return [line.strip().split() for line in file]


def part1(lines: list[tuple[str, str]]) -> int:
    visited = set()
    acc = 0
    i = 0

    while i not in visited:
        cmd, arg = lines[i]
        visited.add(i)

        match cmd:
            case 'nop':
                i += 1
            case 'acc':
                acc = eval(f'acc {arg}')
                i += 1
            case 'jmp':
                i = eval(f'i {arg}')
    
    return acc


def contains_loop(lines: list[tuple[str, str]]) -> int:
    visited = set()
    acc = 0
    i = 0

    while i < len(lines):
        if i in visited:
            return None

        cmd, arg = lines[i]
        visited.add(i)

        match cmd:
            case 'nop':
                i += 1
            case 'acc':
                acc = eval(f'acc {arg}')
                i += 1
            case 'jmp':
                i = eval(f'i {arg}')
    
    return acc


def part2(lines: list[tuple[str, str]]) -> int:
    for i, (cmd, arg) in enumerate(lines):
        if cmd in ['jmp', 'nop']:
            lines[i] = ('nop' if cmd == 'jmp' else 'jmp', arg)
            result = contains_loop(lines)
            if result is not None:
                return result
            lines[i] = (cmd, arg)


def main():
    lines = parse_input('in.txt')

    print('part 1:', part1(lines))
    print('part 2:', part2(lines))


if __name__ == '__main__':
    main()
