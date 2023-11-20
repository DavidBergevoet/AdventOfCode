#![allow(dead_code)]

pub struct Matrix<T: std::clone::Clone + std::fmt::Display> {
    rows: usize,
    columns: usize,
    matrix: Vec<Vec<T>>
}

pub struct Point {
    pub r: usize,
    pub c: usize
}

impl<T: std::clone::Clone + std::fmt::Display> Matrix<T> {
    // Public
    pub fn new(rows: usize, columns: usize, default_value: T) -> Self {
        Matrix {
            rows: rows,
            columns: columns,
            matrix: { let mut vec = Vec::new(); vec.resize(rows, Vec::new()); for col in &mut vec { col.resize(columns, default_value.clone()) }; vec }
        }
    }

    pub fn get(&self, row: usize, col: usize) -> &T {
        assert!(self.matrix.len() > row);
        assert!(self.matrix[row].len() > col);
        &self.matrix[row][col]
    }
    pub fn set(&mut self, row: usize, col: usize, value: T) {
        assert!(self.matrix.len() > row);
        assert!(self.matrix[row].len() > col);
        self.matrix[row][col] = value;
    }

    pub fn print(&self) {
        println!("Matrix<{0}, {1}>", self.rows, self.columns);
        for row in &self.matrix {
            for col in row {
                print!("{} | ", col);
            }
            println!();
        }        
    }

    pub fn get_adjacent_points(&self, row: usize, col: usize, diagonal: bool) -> Vec<Point> {
        let mut result = Vec::new();
        if row == 0 {
            if col == 0 {
                result.push(Point{ r: row + 0, c: col + 1 });
                result.push(Point{ r: row + 1, c: col + 0 });
                if diagonal {
                    result.push(Point{ r: row + 1, c: col + 1 });
                }
            }
            else if col == self.columns -1 {
                result.push(Point{ r: row + 0, c: col - 1 });
                result.push(Point{ r: row + 1, c: col + 0 });
                if diagonal {
                    result.push(Point{ r: row + 1, c: col - 1 });
                }
            }
            else {
                result.push(Point{ r: row + 0, c: col - 1 });
                result.push(Point{ r: row + 0, c: col + 1 });
                result.push(Point{ r: row + 1, c: col + 0 });
                if diagonal {
                    result.push(Point{ r: row + 1, c: col - 1 });
                    result.push(Point{ r: row + 1, c: col + 1 });
                }
            }
        }
        else if row == self.rows - 1 {
            if col == 0 {
                result.push(Point{ r: row - 1, c: col + 0 });
                result.push(Point{ r: row + 0, c: col + 1 });
                if diagonal {
                    result.push(Point{ r: row - 1, c: col + 1 });
                }
            }
            else if col == self.columns - 1 {
                result.push(Point{ r: row - 1, c: col + 0 });
                result.push(Point{ r: row + 0, c: col - 1 });
                if diagonal {
                    result.push(Point{ r: row - 1, c: col - 1 });
                }
            } else {
                result.push(Point{ r: row + 0, c: col - 1 });
                result.push(Point{ r: row + 0, c: col + 1 });
                result.push(Point{ r: row - 1, c: col + 0 });
                if diagonal {
                    result.push(Point{ r: row - 1, c: col + 1 });
                    result.push(Point{ r: row - 1, c: col - 1 });
                }
            }
        }
        else {
            if col == 0 {
                result.push(Point{ r: row - 1, c: col + 0 });
                result.push(Point{ r: row + 0, c: col + 1 });
                result.push(Point{ r: row + 1, c: col + 0 });
                if diagonal {
                    result.push(Point{ r: row + 1, c: col + 1 });
                    result.push(Point{ r: row - 1, c: col + 1 });
                }
            }
            else if col == self.columns - 1 {
                result.push(Point{ r: row - 1, c: col + 0 });
                result.push(Point{ r: row + 1, c: col + 0 });
                result.push(Point{ r: row + 0, c: col - 1 });
                if diagonal {
                    result.push(Point{ r: row - 1, c: col - 1 });
                    result.push(Point{ r: row + 1, c: col - 1 });
                }
            }
            else {
                result.push(Point{ r: row - 1, c: col + 0 });
                result.push(Point{ r: row + 0, c: col + 1 });
                result.push(Point{ r: row + 1, c: col + 0 });
                result.push(Point{ r: row + 0, c: col - 1 });
                if diagonal {
                    result.push(Point{ r: row + 1, c: col - 1 });
                    result.push(Point{ r: row + 1, c: col + 1 });
                    result.push(Point{ r: row - 1, c: col - 1 });
                    result.push(Point{ r: row - 1, c: col + 1 });
                }
            }
        }
        result
    }
    // Private

}