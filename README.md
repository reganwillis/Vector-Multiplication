# Vector Multiplication

This program can multiply very large numbers--potentially thousands of digits. The C++ integer data type cannot hold very large numbers, so to make the multiplication possible I used a vector of integers to store the numbers. I implemented two algorithms with this program: a brute force styled algorithm written by me and the Karatsuba algorithm. I also created helper methods that could add and subtract vectors of integers and return a vector to be used with the two algorithms.

## Installation and Use

You can run this program on any computer or virtual machine with a Linux kernel. 
In the command prompt navigate to the folder where the program was downloaded and type: 
__g++ -Wall -std=c++11 largeNumberMultiplication.cpp__
This will compile the code so it is executable. The default name for the executable file will be a.out so you can type __./a.out__ to run the program. You will see a cursor running and will be able to input two numbers in the form of __x\*y__. This programming does not check for valid input so you will need to type the input with no spaces or non-integer character and ensuring the multiplication sign is in the middle. The input should be entered with the larger number on the left side.

example:
input: 480206450526460879603316532635846\*21789169871971286
output:
B: 10463299924137431288618787106491550779513606317956
K: 10463299924137431288618787106491550779513606317956

The B shows the brute force algorithm, while the K shows the Karatsuba algorithm. They are two different styles of solving the same problem and will have the same answer.
