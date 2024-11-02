fn main(){
    let x = 3 * (1 + 2) + -3 as i32;
    let y : i32;
    let x : f32 = 3.0 + 4.0;
    let z = 2 * x;;;;
    let a : [[i32; 2]; 3] = [[1, 2], [3, 4], [5, 6]];
    let mut t = 0;
    t += 1;
    3 + 2 / (4 - 1);
    let b = a[1][2];

    if x > 5.0 {
        y = 1;
    }
    else if x < 5.0 {
        y = 0;
    }
    else {
        y = 2;
    }

    while x < 10.0 {
        x = x + 1.0;
    }

    for i in 0..5 {
        continue;
    }

    {
        let x = 3;
        {
            let x = 4;
        }
    }
}



