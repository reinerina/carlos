fn main() {
    let mut x : i32;
    stdin(x);
    let mut a = 1;
    let mut b = 1;
    for i in 0..x {
        if x > 2 {
            stdout('H');
            break;
        } else if x < 0 {
            stdout('E');
        } else {
            stdout('L');
        }
    }
}