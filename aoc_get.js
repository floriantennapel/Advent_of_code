const args = process.argv;
if (args.length != 4) {
    console.log(`USAGE: ${args[0]} ${args[1]} [DAY] [YEAR]`);
    process.exit(1);
}

const day = parseInt(args[2]);
if (day < 1 || day > 25) {
    console.log(`invalid day: ${day}`);
    process.exit(1);
}
const year = parseInt(args[3]);
if (isNaN(year) || year < 2015 || year > 2035) {
    console.log(`invalid year: ${year}`);
    process.exit(1);
}

const cookie = ''; // your session cookie here 
const url = `https://adventofcode.com/${year}/day/${day}/input`;
fetch(url, {
    method: 'GET',
    credentials: 'include',
    headers: {
        'Cookie': `session=${cookie}`
    }
})
.then(r => r.text())
.then(t => console.log(t))
.catch(e => console.log(e));
