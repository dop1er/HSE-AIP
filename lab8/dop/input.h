#ifndef INPUT_H
#define INPUT_H

int inputPositiveNumber(const char* prompt);
int* inputNumbers(int maxN, int* actualN);
void printNumbers(int* numbers, int N);
int askYesNo(const char* prompt);

#endif