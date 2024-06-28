def parse_input(filename: str) -> list[list[bool]]:
    with open(filename) as file:
        return [[c == 'L' for c in line.strip()] for line in file]


def part1_adj(pos: tuple[int, int], seating: list[list[bool]]) -> int:
    r, c = pos
    r1 = max(0, r-1)
    c1 = max(0, c-1)
    r2 = min(len(seating)-1, r+1)
    c2 = min(len(seating[0])-1, c+1)

    sum = 0
    for i in range(r1, r2+1):
        for j in range(c1, c2+1):
            if (i, j) == pos:
                continue
            if seating[i][j]:
                sum += 1
    
    return sum


def part2_adj(pos: tuple[int, int], seats: list[list[bool]], current_seating: list[list[bool]]) -> int:
    sum = 0

    for dr in range(-1, 2):
        for dc in range(-1, 2):
            if dr == dc == 0:
                continue

            current = (pos[0] + dr, pos[1] + dc)
            while 0 <= current[0] < len(current_seating) and 0 <= current[1] < len(current_seating[0]):
                if seats[current[0]][current[1]]:
                    if current_seating[current[0]][current[1]]:
                        sum += 1
                    break

                current = (current[0] + dr, current[1] + dc)
    
    return sum


def seat_round(seats: list[list[bool]], current_seating: list[list[bool]], part1: bool) -> tuple[list[list[bool]], int]:
    rows, cols = len(seats), len(seats[0])

    new = [[False for _ in range(cols)] for _ in range(rows)]
    swaps = 0

    for i, row in enumerate(current_seating):
        for j, seat in enumerate(row):
            if not seats[i][j]:
                continue

            adj = part1_adj((i, j), current_seating) if part1 else part2_adj((i, j), seats, current_seating)
            max_adj = 4 if part1 else 5

            if (not seat and adj == 0) or (seat and adj >= max_adj):
                new[i][j] = not seat
                swaps += 1
            else:
                new[i][j] = seat

    return (new, swaps)
        

def count_taken_seats(seats: list[list[bool]], part1: bool) -> int:
    current = [[False for _ in seats[0]] for _ in seats]
    swaps = -1

    while swaps != 0:
        current, swaps = seat_round(seats, current, part1)
    
    return sum([r.count(True) for r in current])


def main():
    seats = parse_input('in.txt')

    print('part 1:', count_taken_seats(seats, True))
    print('part 2:', count_taken_seats(seats, False))


if __name__ == '__main__':
    main()




    

