#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <stdio.h>
#include <windows.h>
#include <math.h>

void ConvertToSI(int LenOfArr, char var_unit[], double *var, const char* PhysParam[], const double DoublePhysParam[]);
void check_user_input(char UserInput[256], int* isNdecimal, int* isInputCorrect, int allowNegative);
void string_to_decimal(char UserInput[256], double* destination_var);
void string_to_integer(char UserInput[256], double*  destination_var);
int isvalidinput(HWND hwnd, HWND hEditField, double *var, int allowNegative);

#endif //INPUT_VALIDATION_H