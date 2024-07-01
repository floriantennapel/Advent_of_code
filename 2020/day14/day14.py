def part1_mask(mask: str, n: int) -> int:
    bin = format(n, '036b')
    return int(''.join([m if m != 'X' else b for m, b in zip(mask, bin)]), 2)


def part2_mask(mask: str, n: int) -> list[int]:
    addresses = mask_addr(''.join([m if m == 'X' else str(int(m) | int(d)) for m, d in zip(mask, format(n, '036b'))]))
    return [int(b, 2) for b in addresses]


def mask_addr(num: str) -> list[str]:
    if not 'X' in num:
        return [num]

    for i, d in enumerate(num):
        if d == 'X':
            return mask_addr(num[:i] + '0' + num[i+1:]) + mask_addr(num[:i] + '1' + num[i+1:])


def run_decoder(lines: list[str], part1: bool = True) -> int:
    mem = dict()
    mask = ''

    for line in lines:
        com, val = line.split(' = ')
        if com == 'mask':
            mask = val
        elif part1:
            exec(f'{com} =  {part1_mask(mask, int(val))}')
        else:
            for addr in part2_mask(mask, int(com[4:-1])):
                mem[addr] = int(val)

    return sum(mem.values())


def main():
    filename = 'in.txt'
    with open(filename) as file:
        lines = file.read().splitlines()
    
    print('part 1:', run_decoder(lines))
    print('part 2:', run_decoder(lines, False))


if __name__ == '__main__':
    main()


