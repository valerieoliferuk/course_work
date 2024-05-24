#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "input_validation.h"

void ConvertToSI(int LenOfArr, char var_unit[], double *var, const char* PhysParam[], const double DoublePhysParam[]){
    for (int i = 0; i < LenOfArr; ++i){
        if (*var_unit == *PhysParam[i]){
            *var = (*var) * (DoublePhysParam[i]);
            break;
        }
    }
}

void check_user_input(char UserInput[256], int* isNdecimal, int* isInputCorrect, int allowNegative) {
    int LenOfString = strlen(UserInput);

    *isNdecimal = 0;
    *isInputCorrect = 1;

    int start = 0;

    // Check for optional leading minus sign
    if (allowNegative && UserInput[0] == '-') {
        if (LenOfString == 1) { // If only a minus sign is present, it's incorrect
            *isInputCorrect = 0;
            return;
        }
        start = 1;
    }

    int hasDecimalPoint = 0;
    for (int i = start; i < LenOfString; ++i) {
        if (i == start) {
            // First character after optional minus sign must be a digit or a decimal point/comma
            if (!isdigit(UserInput[i]) && UserInput[i] != '.' && UserInput[i] != ',') {
                *isInputCorrect = 0;
                return;
            }
        }

        if (UserInput[i] == '.' || UserInput[i] == ',') {
            if (hasDecimalPoint) { // More than one decimal point/comma is incorrect
                *isInputCorrect = 0;
                return;
            }
            hasDecimalPoint = 1;
            *isNdecimal = 1; // Mark as decimal if there's a decimal point/comma
        } else if (!isdigit(UserInput[i])) {
            *isInputCorrect = 0;
            return;
        }
    }

    // Edge case: if the input is just a minus sign or ends with a decimal point/comma
    if ((start == 1 && LenOfString == 1) || (hasDecimalPoint && (UserInput[LenOfString - 1] == '.' || UserInput[LenOfString - 1] == ','))) {
        *isInputCorrect = 0;
    }
}



void string_to_decimal(char UserInput[256], double* destination_var){
    *destination_var = 0.0;
    int LenOfString = strlen(UserInput);
    if (UserInput[1]==','||UserInput[1]=='.'){
    for (int i=0; i < LenOfString; ++i){
        if (i==0){
            *destination_var += ((int)(UserInput[0]-'0'));
            continue;
        }else if (i==1){
            continue;
        }
        *destination_var += ((int)(UserInput[i]-'0'))*(pow(10,(-i+1)));
    }
    }else{
        int position_of_punct_mark = 0;
        char* ptr_to_position_of_punct_mark;
        char decimal_part[256];
        char comma = ',';
        char period = '.';
        if (!strchr(UserInput, comma)){
            ptr_to_position_of_punct_mark = strchr(UserInput, period);
        }else{
            ptr_to_position_of_punct_mark = strchr(UserInput,comma);
        }

        position_of_punct_mark = ptr_to_position_of_punct_mark - UserInput;

        for (int i=0; i<position_of_punct_mark;++i){
            *destination_var += ((int)(UserInput[i]-'0'))*pow(10,position_of_punct_mark-i-1);
        }

        strcpy(decimal_part,UserInput+position_of_punct_mark);
        for (int i=1; i<strlen(decimal_part); ++i){
            *destination_var += ((int)(decimal_part[i]-'0'))*(pow(10,(-i)));
        }

    }
}

void string_to_integer(char UserInput[256], double*  destination_var){
    *destination_var = 0;
    int LenOfString = strlen(UserInput);
    for (int i=0; i < LenOfString; ++i){
        *destination_var += ((int)(UserInput[i]-'0'))*(pow(10,(LenOfString-i-1)));
    }
}

int isvalidinput(HWND hwnd, HWND hEditField, double *var, int allowNegative){

    char buffer1[256];
    GetWindowText(hEditField, buffer1, sizeof(buffer1));

    int isNumDecimal = 0;    // 0 if number is integer, 1 if number is decimal
    int is_valid_input = 1;

    check_user_input(buffer1, &isNumDecimal, &is_valid_input, allowNegative);

    if (!is_valid_input && allowNegative==0){
        MessageBoxW(hwnd,L"Enter the positive numbers only", L"Error", MB_OK);
        return 0;
    }else if (!is_valid_input && allowNegative==1){
        MessageBoxW(hwnd,L"Enter numbers only", L"Error", MB_OK);
        return 0;
    }
    if (isNumDecimal){
        *var = 0.0;
        string_to_decimal(buffer1, var);
                        
    }else{
        *var = 0;
        string_to_integer(buffer1, var);
    }
    return 1;

}
