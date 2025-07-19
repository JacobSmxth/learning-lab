fn main() {
    let x = 5;
    println!("The current x value is {x}");
    println!("This is another way of doing inline thingys. Reminds me of C. {} is the value of x.", x);
    // x = 6 this wouldnt work
    let mut y = 6;
    println!("y is {y}");
    y = 10;
    println!("Y is now {y}");
    println!("Hello, world!");
    // Constants
    //
    //
    const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;
    println!("{}", THREE_HOURS_IN_SECONDS);

    let b = 22;
    let b = b + 1;
    println!("{b}");



    let spaces = "   ";
    let spaces = spaces.len();

    println!("{spaces}");

    // Data Types and Stuff
    //
    //


    //let guess = "42".parse().expect("Not a number!"); // Won't work because you need to put the
    // type annotation

    let guess : u32 = "42".parse().expect("Not a number!");
    println!("{guess}");


}
