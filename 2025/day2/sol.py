def is_invalid(n_str, dividents):
    l = len(n_str)
    for d in dividents:
        if d > l:
            break
        if l%d != 0:
            continue
        s = l // d
        orig = n_str[:s]

        for i in range(1, d):
            if n_str[s*i:s*(i+1)] != orig:
                break 
        else:
            return True
    return False

if __name__ == '__main__':
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23]
    intervals = (map(int, i.split('-')) for i in input().split(','))

    sum_p1 = sum_p2 = 0
    for a, b in intervals:
        for i in range(a, b+1):
            as_str = str(i)
            if is_invalid(as_str, primes):
                sum_p2 += i
                if is_invalid(as_str, [2]):
                    sum_p1 += i

    print(f'part 1: {sum_p1}')
    print(f'part 2: {sum_p2}')
