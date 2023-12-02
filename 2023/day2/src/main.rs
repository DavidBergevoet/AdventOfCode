use std::env;
extern crate file_handler;
extern crate matrix;

fn part1(handler: file_handler::FileHandler) {
    let max_red = 12;
    let max_green = 13;
    let max_blue = 14;

    let mut sum = 0;

    for i in 0..handler.file_content.len() {
        let split_line = handler.get_line_split(i, ' ');
        // println!("Game {}", i + 1);
        let mut game_valid = true;
        for j in (2..split_line.len()).step_by(2) {
            // println!("{}", split_line[j]);
            let number = split_line[j].parse::<u32>().unwrap();
            let color = split_line[j + 1];
            if color.contains("red") && number > max_red {
                // println!("Red contains more {}", number);
                game_valid = false;
            }
            if color.contains("blue") && number > max_blue {
                // println!("Blue contains more {}", number);
                game_valid = false;
            }
            if color.contains("green") && number > max_green {
                // println!("Green contains more {}", number);
                game_valid = false;
            }
        }
        if game_valid {
            sum += i + 1;
        }
    }
    println!("Part 1: Sum {}", sum);
}

fn part2(handler: file_handler::FileHandler) {
    let mut sum = 0;

    for i in 0..handler.file_content.len() {
        let split_line = handler.get_line_split(i, ' ');

        let mut min_red = 0;
        let mut min_blue = 0;
        let mut min_green = 0;

        for j in (2..split_line.len()).step_by(2) {
            let number = split_line[j].parse::<u32>().unwrap();
            let color = split_line[j + 1];
            if color.contains("red") && number > min_red {
                min_red = number;
            }
            if color.contains("blue") && number > min_blue {
                min_blue = number;
            }
            if color.contains("green") && number > min_green {
                min_green = number;
            }
        }
        sum += min_red * min_blue * min_green;
    }
    println!("Part 2: Sum {}", sum);
}

fn main() {
    // Get arguments
    let args: Vec<String> = env::args().collect();
    
    let handler = file_handler::FileHandler::new(&args[1]);
    part1(handler);
    let part2handler = file_handler::FileHandler::new(&args[1]);
    part2(part2handler);
}
