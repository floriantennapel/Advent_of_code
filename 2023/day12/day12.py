memo = dict()

def remove_redundant(line: str) -> str:
    s = [line[0]]
    for c in line[1:]:
        if c == s[-1] == '.':
            continue
        s.append(c)

    return ''.join(s).strip('.')


def count_arrs(line: str, nums: tuple[int]):
    cleaned = line.strip('.')
    key = (cleaned, nums)

    if key in memo:
        return memo[key]

    if sum(nums) > len(cleaned) - cleaned.count('.'):
        memo[key] = 0
        return 0
    
    if len(cleaned) == 0:
        if len(nums) != 0:
            memo[key] = 0
            return 0
        else:
            memo[key] = 1
            return 1
    
    if len(nums) == 0:
        if '#' in cleaned:
            memo[key] = 0
            return 0
        else:
            memo[key] = 1
            return 1
    
    n = nums[0]

    match cleaned[0]:
        case '#':
            if any(c == '.' for c in cleaned[:n]) or (len(cleaned) > n and cleaned[n] == '#'):
                memo[key] = 0
                return 0
            result = count_arrs(cleaned[n+1:], nums[1:])
            memo[key] = result
            return result
        case '?':
            summed = 0
            for c in '#.':
                summed += count_arrs(c + cleaned[1:], nums)
            memo[key] = summed
            return summed


def part1(lines: list[str]) -> int:
    sum = 0
    for line in lines:
        springs, nums = line.split(' ')
        nums = tuple(int(d) for d in nums.split(','))
        sum += count_arrs(remove_redundant(springs), nums)
    
    return sum


def part2(lines: list[str]) -> int:
    sum = 0
    for line in lines:
        springs, nums = line.split(' ')
        springs = remove_redundant('?'.join([springs for _ in range(5)]))
        nums = tuple([int(d) for d in nums.split(',')]*5)
        
        sum += count_arrs(springs, nums)
    
    return sum


def main():
    filename = 'inputData.txt'
    with open(filename) as file:
        lines = file.read().splitlines()
    
    print('part 1:', part1(lines))
    print('part 2:', part2(lines))

    
if __name__ == '__main__':
    main()

