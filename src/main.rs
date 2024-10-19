use std::{fs, usize};
// use std::env
// use std::io::{self,BufReader,BufRead};

const MAX_SEQ: i32 = 509;
const WORDS_COUNT: usize = 500;
const PATH_TO_DATA: &str = "./res/59.500-2";

fn read_lines_into_array(contents: &String, array: &mut [&str]) {

    // println!("contents {}",contents);
    //     .expect("Err to read the file");
    //
    // let words: Vec<&str> = fs::read_to_string(PATH_TO_DATA)
    //     .expect("Err to read the file")
    //     .split_whitespace()
    //     .collect();
    //
    let words:Vec<&str> = contents
        .split_whitespace()
        .collect();
    // let words: Vec<String> = contents
    //     .split_whitespace()
    //     .map(|s| s.to_string())
    //     .collect();
    
    let mut index: usize = 0;
    for word in words {
        array[index] = word;
        index+=1;
    }
}

fn main() {
    let mut lines = ["0"; WORDS_COUNT];
    let contents = fs::read_to_string(PATH_TO_DATA)
        .unwrap();
    let ref_to: &String = &contents;
    read_lines_into_array(ref_to,&mut lines);

    for line in lines {
        println!("{}", line);
    }
}
// function should read file with words 
// convert them 
// return array with ints
// fn read_words() -> [String] {
// }


