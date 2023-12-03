use std::collections::{HashMap, HashSet};
use std::fs;
use std::io::{self, Read};

#[derive(Default)]
struct SchematicNumbers {
    values: Vec<u32>,
    /// Maps coordinates of digits on the schematic to the index on `self.values`
    /// of the number to which they belong
    coordinates: HashMap<(usize, usize), usize>,
}

fn main() -> io::Result<()> {
    let input_file = fs::File::open("input/3.txt")?;
    let bytes = input_file.bytes();

    let (gears, numbers) = parse_file(bytes)?;

    let mut sum = 0;
    for gear in gears {
        if let Some(v) = find_gear_ratio(gear, &numbers) {
            sum += v;
        }
    }

    println!("{sum}");

    Ok(())
}

/// Returns the gear ratio if it is a valid gear,
/// `None` otherwise
fn find_gear_ratio(gear: (usize, usize), numbers: &SchematicNumbers) -> Option<u32> {
    // all the coordinates that border the gear - that is, all the corrdinates
    // that need to be checked for numbers
    let mut check: Vec<(usize, usize)> = Vec::new();

    check.push((gear.0 - 1, gear.1 - 1));
    check.push((gear.0 - 1, gear.1));
    check.push((gear.0 - 1, gear.1 + 1));
    check.push((gear.0, gear.1 - 1));
    check.push((gear.0 + 1, gear.1 - 1));
    check.push((gear.0 + 1, gear.1));
    check.push((gear.0 + 1, gear.1 + 1));

    let mut adjacent = HashSet::new();

    for (x, y) in check {
        if let Some(i) = numbers.coordinates.get(&(x, y)) {
            adjacent.insert(numbers.values[*i]);
            if adjacent.len() > 2 {
                return None;
            }
        }
    }

    if adjacent.len() == 2 {
        return Some(adjacent.iter().product());
    }

    return None;
}

/// Returns an `io::Result` containing a tuple of:
/// 1. A `Vec` containing every point on the grid where there is a gear
/// 2. A `SchematicNumbers` representing the numbers on the schematic
fn parse_file(bytes: io::Bytes<fs::File>) -> io::Result<(Vec<(usize, usize)>, SchematicNumbers)> {
    let mut gears: Vec<(usize, usize)> = Vec::new();
    let mut numbers: SchematicNumbers = SchematicNumbers::default();

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
            for i in (x - num_digits)..x {
                numbers.coordinates.insert((i, y), numbers.values.len());
            }
            numbers.values.push(number);

            number = 0;
            num_digits = 0;
        }

        if b == b'\n' {
            x = 0;
            y += 1;
            continue;
        }

        if b == b'*' {
            gears.push((x, y));
        }
    }

    Ok((gears, numbers))
}
