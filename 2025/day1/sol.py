from sys import stdin

pos = 50
count_p1 = count_p2 = 0

for l in stdin:
    move = int(l[1:])
    sign = -1 if l[0] == 'L' else 1
    if sign == -1:
        if pos <= move and pos != 0:
            move -= pos
            pos = 0
            count_p2 += 1
    else:
        if (100-pos) <= move and pos != 0:
            move -= (100-pos)
            pos = 0
            count_p2 += 1
    pos = (sign*move + pos) % 100

    if pos == 0:
        count_p1 += 1
    count_p2 += int(move / 100)

print(f'part 1: {count_p1}')
print(f'part 2: {count_p2}')
