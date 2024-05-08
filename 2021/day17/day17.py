target_x = (248, 285)
target_y = (-85,-56)

min_x_vel = 22 # smallest value with a triangle number larger than target_x[0] 
max_x_vel = target_x[1]

min_y_vel = target_y[0]
max_y_vel = int((target_y[0] * (target_y[0] - 1)) / 2) + target_y[0]

def within_target(pos):
    return (pos[0] >= target_x[0]) and (pos[0] <= target_x[1]) and (pos[1] >= target_y[0]) and (pos[1] <= target_y[1])

def valid_shot(velocity):
    d_x = velocity[0]
    d_y = velocity[1]
    pos = [d_x, d_y]

    while pos[0] <= target_x[1] and pos[1] >= target_y[0]:
        if within_target(pos):
            return True
        
        d_x = max(d_x - 1, 0)
        d_y -= 1

        pos[0] += d_x
        pos[1] += d_y

    return False

def part2():
    sum = 0

    for x in range(min_x_vel, max_x_vel + 1):
        for y in range(min_y_vel, max_y_vel + 1):
            if (valid_shot((x, y))):
                sum += 1

    return sum

# (triangle number of abs(lowest y)) + lowest y
print('part1:', max_y_vel)
print('part2:', part2())
