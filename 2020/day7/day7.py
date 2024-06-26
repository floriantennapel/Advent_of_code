def parse_input(filename: str) -> dict[str, list[tuple[str, int]]]:
    with open(filename) as file:
        lines = file.read().splitlines()
    bags = dict()

    for line in lines:
        key, rest = line.split(' bags contain ')

        if rest == 'no other bags.':
            bags[key] = []
        else:
            bags[key] = [(f'{s[1]} {s[2]}', int(s[0])) for s in [r.split() for r in rest.split(', ')]]
    
    return bags


checked_contains = dict()
def contains_gold(bag: str, bags: dict[str, list[tuple[str, int]]]) -> bool:
    if bag in checked_contains:
        return checked_contains[bag]
    
    if 'shiny gold' in [bs[0] for bs in bags[bag]]:
        checked_contains[bag] = True
        return True
    
    for next, _ in bags[bag]:
        if contains_gold(next, bags):
            checked_contains[bag] = True
            return True
    
    checked_contains[bag] = False
    return False


checked_count = dict()
def count_bags(bag: str, bags: dict[str, list[tuple[str, int]]]) -> int:
    if bag in checked_count:
        return checked_count[bag]
    
    sum = 0
    for next, c in bags[bag]:
        sum += c * (count_bags(next, bags) + 1) 

    checked_count[bag] = sum
    return sum


def part1(bags: dict[str, list[tuple[str, int]]]) -> int:
    return sum([1 if contains_gold(bag, bags) else 0 for bag in bags])


def main():
    bags = parse_input('in.txt')

    print('part 1:', part1(bags))
    print('part 2:', count_bags('shiny gold', bags))


if __name__ == '__main__':
    main()
