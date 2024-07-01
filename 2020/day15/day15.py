from tqdm import trange

def play_game(starter: list[int], rounds: int) -> int:
    nums = dict()
    for i, d in enumerate(starter):
        nums[d] = i

    next = 0

    for i in trange(len(starter), rounds-1):
        tmp = next

        if next in nums:
            next = i - nums[next]
        else:
            next = 0
        
        nums[tmp] = i
    
    return next
    

def main():
    input = [15,12,0,14,3,1]

    print('part 1:', play_game(input, 2020))
    print('part 2:', play_game(input, 30000000))


if __name__ == '__main__':
    main()