def part1(nums: set[int]) -> int:
    for a in nums:
        b = 2020 - a
        if b in nums:
            return a * b


def part2(nums: set[int]) -> int:
    as_list = list(nums)

    for i, a in enumerate(as_list[:-1]):
        for b in as_list[i+1:]:
            c = 2020 - a - b
            if c in nums:
                return a * b * c


def main():
    filename = 'in.txt'
    with open(filename) as file:
        nums = {int(line) for line in file}
    
    print('part 1:', part1(nums))
    print('part 2:', part2(nums))


if __name__ == '__main__':
    main()
