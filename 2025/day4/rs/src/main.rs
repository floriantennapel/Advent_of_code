fn surrounding(r: usize, c: usize, grid: &[Vec<bool>]) -> i32 {
    let mut count = 0;
    for i in r.saturating_sub(1)..(r+2).min(grid.len()) {
        for j in c.saturating_sub(1)..(c+2).min(grid[0].len()) {
            if (i, j) == (r, c) {
                continue;
            }
            if grid[i][j] {
                count += 1;
            }
        }
    }
    return count;
}

fn main() {
    let inp = include_str!("../../in");
    let mut grid = inp
            .lines()
            .map(|l| {l
                .trim()
                .chars()
                .map(|c| {if c == '@' {true} else {false}})
                .collect::<Vec<bool>>()})
            .collect::<Vec<_>>();
    
    let mut p1_done = false;
    let mut total_count = 0;
    loop {
        let mut count = 0;
        for i in 0..grid.len() {
            for j in 0..grid[0].len() {
                if grid[i][j] && surrounding(i, j, &grid) < 4 {
                    count += 1;
                    if p1_done {
                        grid[i][j] = false;
                    }
                }
            }
        }
        if !p1_done {
            println!("part 1: {count}");
            p1_done = true;
        } else {
            total_count += count;
        }

        if count == 0 {
            break;
        }
    }

    println!("part 2: {total_count}");
}
