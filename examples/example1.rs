fn main() {
   let mut amount : i32;
   let bills = [100, 50, 20, 10, 5, 2, 1];
   let mut n_bills = [0; 7];
   stdin(amount);
   for i in 0..7 {
       n_bills[i] = amount / bills[i];
       amount %= bills[i];
       if amount == 0 {
           break;
       }
   }

   for i in 0..7 {
       stdout(n_bills[i], ' ', 'x', ' ', bills[i], '\n');
   }
}