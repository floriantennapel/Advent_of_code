import string

def parse_input(filename: str) -> list[dict[str, str]]:
    with open(filename) as file:
        on_single_lines = []
        s = ''
        for line in file:
            if line.isspace():
                on_single_lines.append(s.strip())
                s = ''
            else:
                s += ' ' + line.strip()
        on_single_lines.append(s.strip())
    
    return [{k: v for k, v in (p.split(':') for p in line.split())} for line in on_single_lines]
        

def all_present(passport) -> bool:
    req = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid']
    for r in req:
        if r not in passport:
            return False
    
    return True


def all_valid(passport) -> bool:
    req = {
        'byr': lambda n: len(n) == 4 and n.isdecimal() and 1920 <= int(n) <= 2002,
        'iyr': lambda n: len(n) == 4 and n.isdecimal() and 2010 <= int(n) <= 2020,
        'eyr': lambda n: len(n) == 4 and n.isdecimal() and 2020 <= int(n) <= 2030,
        'hgt': lambda n: len(n) > 2 and n[:-2].isdecimal() and n[-2:] in ['in', 'cm'] and (150 <= int(n[:-2]) <= 193 if n[-2:] == 'cm' else 59 <= int(n[:-2]) <= 76),
        'hcl': lambda h: len(h) == 7 and h[0] == '#' and all(n in string.hexdigits for n in h[1:]),
        'ecl': lambda e: e in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'],
        'pid': lambda n: len(n) == 9 and n.isdecimal()
    }

    return all(req.get(k, lambda _: True)(v) for k, v in passport.items())


def part1(passports: list[dict[str, str]]) -> int:
    return sum([1 if all_present(p) else 0 for p in passports])


def part2(passports: list[dict[str, str]]) -> int:
    return sum([1 if all_present(p) and all_valid(p) else 0 for p in passports])


def main():
    passports = parse_input('in.txt')

    print('part1:', part1(passports))
    print('part2:', part2(passports))


if __name__ == '__main__':
    main()

