fn main(){
    let mut x = 3 * (1 + 2) + -3 as i32;
    let y : i32;

    let a : [i32; x];
    let b : [[i32; 5]; 6];


    for i in 0..5 {
        let x = 3;
        continue;
    }

    while x < 10 {
        break;
    }

    if x < 10 {
        x += 1;
    } else {
        x -= 1;
    }

    {
        let z = 3;
        {
            let y = 4;
        }
    }
}



