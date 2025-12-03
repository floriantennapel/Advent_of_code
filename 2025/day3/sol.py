from sys import stdin

def jolt(bat, s):
    dp = [[-1]*len(bat) for _ in range(s)]
    sup = -1
    for j in range(len(bat)-1, -1, -1):
        sup = max(sup, bat[j])
        dp[0][j] = sup

    pow = 10
    for i in range(1, s):
        for j in range(len(bat)-1-i, -1, -1):
            sup = max(sup, bat[j]*pow + dp[i-1][j+1])
            dp[i][j] = sup
        pow *= 10

    return dp[s-1][0]

if __name__ == '__main__':
    inp = [list(map(int, line.strip())) for line in stdin]
    print(f'part 1: {sum(jolt(b, 2) for b in inp)}') 
    print(f'part 2: {sum(jolt(b, 12) for b in inp)}')
