fn main() {
    let mut x = [[false; 3]; 3];
    x[2][1] = true;
    for i in 0..3 {
        for j in 0..3 {
            if x[i][j] == true {
                stdout('X');
                continue;
                stdout('Y');
            } else {
                stdout('O');
            }
        }
        stdout('\n');
    }
}