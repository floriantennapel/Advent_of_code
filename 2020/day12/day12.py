import math
import numpy as np

dirs = {
    'N': np.array([0, 1]), 
    'S': np.array([0, -1]), 
    'E': np.array([1, 0]), 
    'W': np.array([-1, 0])
}

def rotate(current_dir: np.array, info: tuple[str, int]) -> np.array:
    dir, d_a = info
    len = np.linalg.norm(current_dir)

    current_angle = np.angle(complex(*current_dir))
    new_angle = current_angle + (1 if dir == 'L' else -1) * d_a * math.pi / 180
    unit_vec = np.array([math.cos(new_angle), math.sin(new_angle)])
    return unit_vec * len


def part1(moves: list[tuple[str, int]]) -> int:
    pos = np.array([0., 0.])
    direction = np.array([1., 0.])

    for dir, amount in moves:
        if dir in dirs:
            pos += dirs[dir] * amount
        elif dir == 'F':
            pos += direction * amount
        else:
            direction = rotate(direction, (dir, amount))
    
    return round(sum(map(abs, pos)))


def part2(moves: list[tuple[str, int]]) -> int:
    pos = np.array([0., 0.])
    waypoint = np.array([10., 1.])

    for dir, amount in moves:
        if dir in dirs:
            waypoint += dirs[dir] * amount
        elif dir in "RL":
            waypoint = rotate(waypoint, (dir, amount))
        else:
            pos += waypoint * amount
    
    return round(sum(map(abs, pos)))


def main():
    filename = 'in.txt'
    with open(filename) as file:
        moves = [(l[0], int(l[1:])) for l in file]
    
    print('part1:', part1(moves))
    print('part2:', part2(moves))


if __name__ == '__main__':
    main()
