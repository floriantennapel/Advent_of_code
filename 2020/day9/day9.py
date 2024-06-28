from collections import deque

def part1(nums: list[int], preamble: int) -> int:
    sums = deque([[] for _ in range(preamble - 1)])

    for i, a in enumerate(nums[:preamble - 1]):
        for b in nums[i+1:preamble]:
            sums[i].append(a + b)
    
    for i, n in enumerate(nums[preamble:]):
        found = False
        for s in sums:
            if n in s:
                found = True
        if not found:
            return n

        sums.popleft()
        
        for j, b in enumerate(nums[i+1:preamble+i]):
            if j < preamble - 2:
                sums[j].append(n + b)
            else:
                sums.append([n + b])


def part2(nums: list[int]) -> int:
    target = part1(nums, 25)

    i, j = 0, 1
    sum = nums[0] + nums[1]

    while True:
        if sum == target:
            return min(nums[i:j+1]) + max(nums[i:j+1])
        elif sum < target:
            j += 1
            sum += nums[j]
        else:
            sum -= nums[i]
            i += 1
            if (i == j): # range must have at least two numbers
                j += 1
                sum += nums[j]
    

def main():
    with open('in.txt') as file:
        nums = [int(n) for n in file]
    
    print('part 1:', part1(nums, 25))
    print('part 2:', part2(nums))


if __name__ == '__main__':
    main()