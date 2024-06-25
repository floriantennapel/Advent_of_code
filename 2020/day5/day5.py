def search(steps: list[bool]) -> int:
    lo, hi = 0, 2**(len(steps)) - 1

    for s in steps:
        if s:
            lo = (hi - lo) // 2 + lo + 1
        else:
            hi = (hi - lo) // 2 + lo
    
    return lo


def seat_id(seat: str) -> int:
    return search([c == 'B' for c in seat[:7]]) * 8 + search([c == 'R' for c in seat[7:]])


def part1(seats: list[str]) -> int:
    return max(seat_id(seat) for seat in seats)


def part2(seats: list[str]) -> int:
    seat_ids = {seat_id(seat) for seat in seats}
    for id in range(min(seat_ids) + 1, max(seat_ids)):
        if id not in seat_ids:
            return id


def main():
    filename = 'in.txt'
    with open(filename) as file:
        seats = file.read().splitlines()
    
    print('part 1:', part1(seats))
    print('part 2:', part2(seats))


if __name__ == '__main__':
    main()