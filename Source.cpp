#include <iostream>
#include <stdio.h>
#include <inttypes.h>
using namespace std;

// task 2.1 line random generator
struct LineGenerator
{
	int divisor; // the number to divide by ('M' in task description)
	int firstNumber; // prime number ('c' in task description)

	LineGenerator(int _divisor, int _firstNumber)
	{
		divisor = _divisor;
		firstNumber = _firstNumber;
	}

	void printRandomNumbers(int amount)
	{
		int a;
		long long int generatedNumber; // 'Xn' in task description
		long long int prevoiusNumbersModulo; // (a1*Xn - 1 + a2 * Xn - 2 + ... + c) mod devisior

		prevoiusNumbersModulo = firstNumber; // first number to add is only 'c'
		generatedNumber = 0; // first iteration doesn't have previous generated number 

		for (int i = 0; i < amount; i++)
		{
			a = rand() % 21;  // random number in range <0;20>
			prevoiusNumbersModulo += (a * generatedNumber) % divisor;
			prevoiusNumbersModulo %= divisor;
			generatedNumber = prevoiusNumbersModulo;

			printf("number %d: %d\n", i, generatedNumber);
		}
	}
};

// task 2.6 shift random generator
struct ShiftGenerator
{
	uint32_t generatedNumber;
	int p;
	int q;

	ShiftGenerator(int firstNumber)
	{
		p = 7;
		q = 3;
		generatedNumber = firstNumber << (31 - (p - 1)); // shift number to first p bytes, zeros on rest
	}

	void printRandomNumbers(int amount)
	{
		uint32_t byteP, byteQ, newByte;
		for (int j = 0; j < amount; j++)
		{		
			for (int i = 31; i > 0; i--)
			{
				uint32_t mask = 1 << i;
				byteP = generatedNumber & mask; // extract first byte to xor
				mask >>= q + 1;
				byteQ = generatedNumber & mask; // extract second byte to xor (placement determinated by q)
				byteP >>= p; // shift first byte to position where it will be inserted (placement determinated by p)
				byteQ >>= (p - (q+1)); // shift second byte to the same place as the first
				newByte = byteP ^ byteQ; // byteP xor byteQ
				generatedNumber = newByte | generatedNumber; // place byte in correct place in number
			}
			printf("number %d: %" PRIu32 "\n", j, generatedNumber);
			generatedNumber <<= (31 - (p - 1)); // shift p last bytes to the first p bytes.
		}
	}
};

int main() {
	
	// task 2.1 line random generator
	int M = (1 << 31) - 1; // 2^31 - 1
	int firstNumber = 6571; // first prime number

	LineGenerator randomGenerator = LineGenerator(M, firstNumber);
	randomGenerator.printRandomNumbers(100000);

	// task 2.6 shift random generator
	firstNumber = 0b1011101;
	ShiftGenerator shiftRandomGenerator = ShiftGenerator(firstNumber);
	shiftRandomGenerator.printRandomNumbers(100000);

	return 0;
}