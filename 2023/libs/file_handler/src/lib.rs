#![allow(dead_code)]

use std::fs;

pub struct FileHandler {
    pub file_name: String,
    pub file_content: Vec<String>
}

impl FileHandler {

    // Public
    pub fn new(file: &str) -> FileHandler {
        FileHandler {
            file_name: file.to_string(),
            file_content: Self::read_file_into_content(file)
        }
    }

    pub fn get_line_split(&self, line_number: usize, seperator: char) -> Vec<&str> {
        self.file_content[line_number].split(seperator).collect::<Vec<&str>>()
    }

    // Private
    fn read_file_into_content(file: &str) -> Vec<String> {
        let mut result = Vec::new();
        for line in fs::read_to_string(file).unwrap().lines() {
            result.push(line.to_string());
        }
        result
    }
}
