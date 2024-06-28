def part1(nums: list[int]) -> int:
    in_order = sorted(nums)

    prev = 0
    diff_1 = 0
    diff_3 = 0

    for n in in_order:
        match n - prev:
            case 1:
                diff_1 += 1
            case 3:
                diff_3 += 1
        
        prev = n

    diff_3 += 1 # adding device

    print(diff_1, diff_3)
    
    return diff_1 * diff_3


memo: dict[tuple[int], int] = dict()
def count_combinations(nums: list[int]) -> int:
    immut = tuple(nums)
    if immut in memo:
        return memo[immut]
    
    if len(nums) == 1:
        memo[immut] = 1
        return 1
    
    sum = 0
    base = nums[0]
    for i in range(1, 4):
        if i >= len(nums) or nums[i] - base > 3:
            break
        sum += count_combinations(nums[i:])
    
    memo[immut] = sum
    return sum


def part2(nums: list[int]) -> int:
    return count_combinations(sorted([0] + nums + [max(nums) + 3]))


def main():
    filename = 'in.txt'

    with open(filename) as file:
        nums = [int(line) for line in file]
    
    print('part 1:', part1(nums))
    print('part 2:', part2(nums))


if __name__ == '__main__':
    main()