# DSBA Introduction to Programming // Workshops 23 and 24
Spring semester 2021/22


Enums, bitwise operations, tests.


## Task 1. Get bit at index.

You are given an integer number **A** and an index **i**. Find and print the bit at position **i** in the number. The least significant bits have the lower indices. 


Example input: 
```
9 1
```
Example output: 
```
0
```
 

## Task 2. Number of ones.

You are given an integer number **A** in the range 0 <= A <= 4*10^18. Print the number of bits set to 1 in the binary representation of *A*. 

Example input: 
```
9 
```
Example output: 
```
2 
```
 

Example input: 
```
126 
```
Example output: 
```
6 
```
 

## Task 3. Output Binary Number.

Write a function that takes an unsigned integer number and prints its binary representation. Print all 32 bits, including leading zeros. Separate groups of 4 bits with apostrophes ('). 

Additional task: 
Implement a version of this function that works with signed integers. 

Example input: 
```
5 
```
Example output: 
```
0000'0000'0000'0000'0000'0000'0000'0101 
```

# Part 2. Tests

Study the structure of the test project, make sure you can run it.

Add a new file bitwise_test.cpp to the project. Implement EXPECT_EQ tests for tasks 1-3 from the previous workshop in this file.

1.  Task 1, getting bit at an index.
    1. Several checks for bits equal to 0 and 1. Use binary literals to define numbers for testing.
    2. Checks for indices 0 and 31 both for numbers where they should be 0 and where they should be 1.
2. Task 2, counting bits equal to 1 in a number.
    1. Checks for a number with 64 ones, 0 ones, some random numbers.
3. Task 3, output.
    1. Rewrite the function to output the number as a string instead of printing it. (If you haven’t finished this function during the last workshop, you may reverse a string instead of directly printing it in the reverse order).
    2. Check 1-2 random numbers.
    3. Check that numbers which have 1 as their first bit are outputted correctly.
    4. If you implemented the signed version of this task, check that it works with negative numbers, including ones which have 0 as their second bit.
