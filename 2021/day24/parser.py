output = open('program.c', 'w')
input = open('in.txt', 'r')

output.write('''
long long monad(char* digit) {
\tlong long w = 0;
\tlong long x = 0;
\tlong long y = 0;
\tlong long z = 0;\n\n''')

for line in input:
    splitted = line.strip().split(' ')
    if (len(splitted) == 3): 
        a, b, c = splitted 
        operator = ''
        match (a):
            case 'add':
                operator = '+='
            case 'mul':
                operator = '*='
            case 'div':
                operator = '/='
            case 'mod':
                operator = '%='
            case 'eql':
                output.write(f'\t{b} = {b} == {c};\n')
                continue

        output.write(f'\t{b} {operator} {c};\n')
    else:
        a, b = splitted
        output.write(f"\t{b} = *(digit++) - '0';\n")

output.write('\n\treturn z;\n}')

