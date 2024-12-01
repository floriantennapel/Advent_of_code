# Advent_of_code
Solutions to Eric Wastl's <a href='https://adventofcode.com/'>christmas coding puzzles<a>

## automatic script
`aoc.sh` will automatically fetch input and run a python, c++ or c file on that input.
solution programs must be named `sol.{py/cpp/c}`.
To use the script and run as `aoc`:
- add your session cookie to the `cookie` variable in `aoc_get.js`
- add absolute path to `Advent_of_code` directory to variable `PATH_TO_AOC` in `aoc.sh`
- make `aoc.sh` executable `chmod +x aoc.sh`
- link `aoc.sh` to PATH, for instance (when in `Advent_of_code` directory) `sudo ln -s "$(pwd)/aoc.sh" /usr/local/bin/aoc`
