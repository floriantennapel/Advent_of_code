use std::{fs::File, io::Read};

fn is_invalid(n: &str, dividents: &[usize]) -> bool {
    let l = n.len();
    'divident_loop: for d in dividents {
        if *d > l {
            break;
        }
        if l % d != 0 {
            continue;
        }
        let s = l/d;
        let orig = &n[..s];

        for i in 1..*d {
            if &n[s*i..s*(i+1)] != orig {
                continue 'divident_loop;
            }
        }
        return true;
    }
    return false;
}

fn main() {
    let primes = vec![2, 3, 5, 7, 11, 13, 17, 19, 23];

    let mut file = File::open("../in").unwrap();
    let mut input = String::new();
    file.read_to_string(&mut input).unwrap();

    let intervals = input
            .trim()
            .split(",")
            .map(|s| {s
                .split("-")
                .map(|splitted|splitted.parse::<usize>().unwrap())
                .collect::<Vec<usize>>()}
            );

    let mut sum_p1: usize = 0;
    let mut sum_p2: usize = 0;

    for interval in intervals {
        let a = interval[0];
        let b = interval[1];

        for i in a..=b {
            let as_str = i.to_string();
            if is_invalid(&as_str, &primes) {
                sum_p2 += i;
                if is_invalid(&as_str, &primes[..1]) {
                    sum_p1 += i;
                }
            }
        }
    }

    println!("part 1: {sum_p1}");
    println!("part 2: {sum_p2}");
}
