fn main() {
    let mut n : i32;
    let mut pi = 3.0;
    let mut sign = 1.0;
    stdin(n);
    for i in 0..n {
        let i = (i as f32 + 1.0) * 2.0;
        let term = 4.0 / (i * (i + 1.0) * (i + 2.0));
        pi += sign * term;
        sign *= -1.0;
    }
    stdout('\n', pi);
}