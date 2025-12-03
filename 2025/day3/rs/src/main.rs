fn jolts(batt: &[u64], m: usize) -> u64 {
    let n = batt.len();
    let mut dp = vec![vec![0; n]; m];

    let mut sup = 0;
    for j in (0..n).rev() {
        sup = sup.max(batt[j]);
        dp[0][j] = sup;
    }

    let mut pow = 10;
    for i in 1..m {
        for j in (0..(n-i)).rev() {
            sup = sup.max(batt[j]*pow + dp[i-1][j+1]);
            dp[i][j] = sup;
        }
        
        pow *= 10;
    }

    return dp[m-1][0];
}

fn main() {
    let inp = include_str!("../../in");
    let (p1, p2) = inp.lines()
            .map(|l| {l.trim()
                .chars()
                .map(|c| {c.to_digit(10).unwrap() as u64})
                .collect::<Vec<u64>>()
            })
            .map(|b| {(jolts(&b, 2), jolts(&b, 12))})
            .fold((0, 0), |(a, b,), (c, d)| {(a+c, b+d)});

    println!("part 1: {}", p1);
    println!("part 2: {}", p2);
}
