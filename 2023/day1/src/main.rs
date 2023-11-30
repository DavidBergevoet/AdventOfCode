use std::env;
extern crate file_handler;
extern crate matrix;

fn main() {
    // Read file
    let file_path = &args[1];
    let contents = fs::read_to_string(file_path).expect("Read file");
}
