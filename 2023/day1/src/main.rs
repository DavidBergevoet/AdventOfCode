use std::env;
use std::collections::HashMap;
extern crate file_handler;
extern crate matrix;

fn part1(handler: file_handler::FileHandler) {
    let mut digit_list = Vec::new();
    for line in handler.file_content {
        let mut first_digit = 99;
        let mut last_digit = 99;
        for character in line.chars() {
            if character.is_numeric() {
                if first_digit == 99 {
                    first_digit = character as u32 - '0' as u32;
                }
                last_digit = character as u32 - '0' as u32;
            }
        }
        let combined_number = first_digit * 10 + last_digit;
        digit_list.push(combined_number);
        // println!("Line '{0}', first {1}, last {2}, combined {3}", line, firstDigit, lastDigit, combinedNumber);
    }

    let sum: u32 = digit_list.iter().sum();
    println!("Part 1: Sum {}", sum)
}

fn part2(handler: file_handler::FileHandler) {
    let mut numbers = HashMap::new();
    numbers.insert(String::from("one"), 1);
    numbers.insert(String::from("two"), 2);
    numbers.insert(String::from("three"), 3);
    numbers.insert(String::from("four"), 4);
    numbers.insert(String::from("five"), 5);
    numbers.insert(String::from("six"), 6);
    numbers.insert(String::from("seven"), 7);
    numbers.insert(String::from("eight"), 8);
    numbers.insert(String::from("nine"), 9);
    let mut digit_list = Vec::new();

    for line in handler.file_content {
        let mut first_digit = 0;
        let mut last_digit = 0;
        let mut my_string = String::from("");
        for character in line.chars() {
            my_string.push(character);
            for (key, value) in &numbers {
                if my_string.contains(key) {
                    if first_digit == 0 {
                        first_digit = *value;
                    }
                    last_digit = *value;
                    my_string = String::from(my_string.chars().last().unwrap());
                }
            }
            if character.is_numeric() {
                if first_digit == 0 {
                    first_digit = character as u32 - '0' as u32;
                }
                last_digit = character as u32 - '0' as u32;
            }
        }
        let combined_number = first_digit * 10 + last_digit;
        println!("Line '{0}'{1},{2},{3}", line, first_digit, last_digit, combined_number);
        digit_list.push(combined_number);
    }
    let sum: u32 = digit_list.iter().sum();
    println!("Part 2: Sum {}", sum)
}

fn main() {
    // Get arguments
    let args: Vec<String> = env::args().collect();
    // Read file
    let handler = file_handler::FileHandler::new(&args[1]);

    // part1(handler);
    part2(handler);
}
