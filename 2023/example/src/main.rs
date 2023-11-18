use std::env;
use std::fs;
extern crate example_lib;
extern crate file_handler;

fn main() {
    // Get arguments
    let args: Vec<String> = env::args().collect();

    println!("Hello, world!{0} {1}",args[0], args[1]);

    // Read file
    let file_path = &args[1];
    let contents = fs::read_to_string(file_path).expect("Read file");

    println!("{}",contents);

    example_lib::lib_function();

    let handler = file_handler::FileHandler::new("input.txt");

    for line in &handler.file_content {
        println!("Line: '{0}'", line)
    }

    for sub in &handler.get_line_split(1, ' ') {
        println!("sub: '{}'", sub);
    }
}
