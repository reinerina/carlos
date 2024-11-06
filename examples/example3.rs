fn main() {
    let mut a : [[i32; 2]; 7];
    for i in 0..7 {
        for j in 0..2 {
            stdin(a[i][j]);
        }
    }

    for i in 0..7 {
        for j in 0..2 {
            stdout(a[i][j], ' ');
        }
        stdout('\n');
    }
}