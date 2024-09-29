from itertools import product

def run_program(noun, verb, prog):
    program = prog[:]
    program[1] = noun
    program[2] = verb

    for i in range(0, len(program), 4):
        op = program[i]
        a = program[program[i+1]]
        b = program[program[i+2]]
        dest = program[i+3]
        match op:
            case 1:
                program[dest] = a + b
            case 2:
                program[dest] = a * b
            case 99:
                return program[0]
                
program = [int(d) for d in input().split(',')]

print(f'part 1: {run_program(12, 2, program)}')

for n, v in product(range(100), range(100)):
    if run_program(n, v, program) == 19690720:
        print(f'part 2: {100 * n + v}')
        exit(0)
