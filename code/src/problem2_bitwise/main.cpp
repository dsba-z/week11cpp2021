#include <iostream>

int getBitAtIndex(unsigned int number, int idx)
{
    int bit = 0;
    return bit;
}


int countOnes(unsigned long long  number)
{
    int count = 0;
    return count;
}

void printBinary(unsigned int  number)
{
    
}

template<typename T>
void testAnswer(int testNum, const std::string message, T answer, T correctAnswer)
{
    std::cout << "Test " << testNum << std::endl;
    std::cout << message << std::endl;
    if (answer == correctAnswer)
    {
        std::cout << "OK" << std::endl;
        return;
    }
    
    std::cout << "Error: ";
    std::cout << "Output is " << answer << std::endl;
    std::cout << "Correct answer is " << correctAnswer << std::endl;
}

int main()
{
    unsigned int  number = 9;
    int idx = 2;
    
// testing function 1
  
    int answer = getBitAtIndex(number, idx);
    int correctAnswer = 0;
    testAnswer(1, "Bit 2 in number 9", answer, correctAnswer);

    answer = getBitAtIndex(number, 3);
    correctAnswer = 1;
    testAnswer(2, "Bit 3 in number 9", answer, correctAnswer);

// testing function 2
    answer = countOnes(126);
    correctAnswer = 6;
    testAnswer(3, "Number of 1-bits in 126", answer, correctAnswer);

    
// testing function 2
    printBinary(9);
    // 0000'0000'0000'0000'0000'0000'0000'1001 
    
    printBinary(2147483647);
    // should be 
    // 0111'1111'1111'1111'1111'1111'1111'1111 
    
    printBinary(1u<<31);
    // should be 
    // 1000'0000'0000'0000'0000'0000'0000'0000 
    
    return 0;
}
