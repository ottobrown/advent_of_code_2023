use std::collections::HashSet;
use std::fs;
use std::io::{self, Read};

#[derive(Eq, Hash, PartialEq, Clone, Copy)]
struct SchematicNumber {
    value: u32,
    num_digits: usize,
    x: usize,
    y: usize,
}

fn main() -> io::Result<()> {
    let input_file = fs::File::open("input/3.txt")?;
    let bytes = input_file.bytes();

    let (symbols, numbers) = parse_file(bytes)?;

    let mut sum = 0;
    for number in numbers {
        if !is_adjacent(number, &symbols) {
            sum += number.value;
        }
    }

    println!("{sum}");

    Ok(())
}

/// Returns `true` if the number is adjacent to any point in `symbols`,
/// orthogonally or diagonally.
fn is_adjacent(number: SchematicNumber, symbols: &HashSet<(usize, usize)>) -> bool {
    let mut adjacent: HashSet<(usize, usize)> = HashSet::new();

    // Insert point left of leftmost digit and top and bottom left corners
    let left = number.x - 1;

    adjacent.insert((left, number.y));
    adjacent.insert((left, number.y + 1));
    adjacent.insert((left, number.y - 1));

    // Insert point right of rightmost digit and top and bottom right corners
    let right = number.x + number.num_digits;

    adjacent.insert((right, number.y));
    adjacent.insert((right, number.y + 1));
    adjacent.insert((right, number.y - 1));

    // Insert points above and below each digit of the number
    for i in 0..number.num_digits {
        let x = number.x + i;

        adjacent.insert((x, number.y + 1));
        adjacent.insert((x, number.y - 1));
    }

    adjacent.is_disjoint(symbols)
}

/// Returns an `io::Result` containing a tuple of:
/// 1. A `HashSet` containing every point on the grid where there is a symbol
/// 2. A `Vec` containing a `SchematicNumber` for each number on the schematic
fn parse_file(
    bytes: io::Bytes<fs::File>,
) -> io::Result<(HashSet<(usize, usize)>, Vec<SchematicNumber>)> {
    let mut symbols: HashSet<(usize, usize)> = HashSet::new();
    let mut numbers: Vec<SchematicNumber> = Vec::new();

    // The coordinates are 1-indexed, so `y` is initialized to `1` and
    // `x` becomes `1` at the very beginning of the loop
    let mut x: usize = 0;
    let mut y: usize = 1;

    let mut number = 0;
    let mut num_digits = 0;

    for byte in bytes {
        let b = byte?;

        x += 1;

        if b.is_ascii_digit() {
            number *= 10;
            number += (b - b'0') as u32;
            num_digits += 1;
            continue;
        } else if num_digits > 0 {
            numbers.push(SchematicNumber {
                value: number,
                num_digits,
                x: x - num_digits,
                y,
            });

            number = 0;
            num_digits = 0;
        }

        if b == b'\n' {
            x = 0;
            y += 1;
            continue;
        }

        if b == b'.' || b == b'\r' {
            continue;
        }

        // `b` is not a digit, carriage return, line feed, or period -
        // therefore it is a symbol
        symbols.insert((x, y));
    }

    Ok((symbols, numbers))
}
