fn main(){
    let x = 3 * (1 + 2) + -3 as i32;
    let y : i32;
    let mut x : f32 = 3.0 + 4.0;


    for i in 0..5 {
        let x = 3;
        continue;
    }

    while x < 10.0 {
        break;
    }

    if x < 10.0 {
        x += 1.0;
    } else {
        x -= 1.0;
    }

    {
        let z = 3;
        {
            let y = 4;
        }
    }
}



