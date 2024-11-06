fn main() {
    let mut x : i32;
    stdin(x);
    let mut a = 1;
    let mut b = 1;
    for i in 0..x {
        let i = a;
        stdout(' ', i);
        a += b;
    }
    let a = a;
    stdout('\n', a);
}