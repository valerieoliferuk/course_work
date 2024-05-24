#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "input_validation.h"

#define g 9.80665
#define M_PI 3.14159265358979323846
#define R 8.31446261815324 // Ideal gas constant

#define MECHANICS_BUTTON 1
#define THERMODYNAMICS_BUTTON 2

#define FRICTION_CALCULATOR 1
#define INCLINED_PLANE_CALCULATOR 2
#define FREE_FALL_CALCULATOR 3

#define FRICTION_CALCULATOR_BUTTON 1
#define FF_CALCULATOR_BUTTON_TIME_OF_FALL 2
#define FF_CALCULATOR_BUTTON_VELOCITY 3

#define INCLINED_PLANE_CALCULATOR_BUTTON 1

#define EFFICIENCY_CALCULATOR 1
#define IDEAL_GAS_LAW_CALCULATOR 2
#define THERMAL_EFFICIENCY_CALCULATOR 3

#define EFFICIENCY_CALCULATOR_BUTTON 1
#define VELOCITY_ADDITION_CALCULATOR 1

#define COMBOBOX_FORCE 1
#define COMBOBOX_ENERGY_INPUT 2
#define COMBOBOX_ENERGY_OUTPUT 3
#define COMBOBOX_VELOCITY 4
#define COMBOBOX_HEIGHT 5
#define COMBOBOX_MASS 6
#define COMBOBOX_ANGLE 7


const char* force[] = {"Newtons","Kilonewtons", "Meganewtons"};
const double DoubleForce[]={1, 100, 1000000};

const char* energy[] = {"Joules","Kilojoules", "Megajoules", "Watt hours", "Kilowatt hours"};
const double DoubleEnergy[]={1,100 ,1000000, 3600, 360000};

const char* Velocity[] = {"M/s", "Km/h"};
const double DoubleVelocity[] = {1, 3.6};

const char* Height[] = {"Cm", "M", "Km"};
const double DoubleHeight[] = {0.01, 1, 1000};

const char* Current[] = {"Microamperes", "Milliamperes", "Amperes"};
const double DoubleCurrent[] = {0.000001, 0.001, 1};

const char* Mass[] = {"Grams", "Kilograms"};
const double DoubleMass[] = {0.001, 1};

const char* Angle[] = {"Degrees", "Radians"};
const double DoubleAngle[] = {1, 180/M_PI};

const char* Pressure[] = {"Pascals(Pa)", "Kilopascals(kPa)", "Megapascals(MPa)", "Bars(bar)"};
const double DoublePressure[] = {1, 0.001, 0.000001, 0.00001};

const char* Volume[] = {"Cubic milimeters(mm^3)", "Cubic cantimeters(cm^3)", "Cubic meters(m^3)", "Mililiters(ml)", "Liters(l)"};
const double DoubleVolume[] = {0.000000001, 0.000001, 1, 0.000001, 0.001};

LRESULT CALLBACK WindowProcedure(HWND, UINT,WPARAM,LPARAM);

LRESULT CALLBACK WindowMechanics(HWND, UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowFrictionCalc(HWND, UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowInclinedPlaneCalc(HWND, UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowFreeFallCalc(HWND, UINT,WPARAM,LPARAM);

LRESULT CALLBACK WindowThermodynamics(HWND, UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowEfficiencyCalc(HWND, UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowIdealGasLawCalc(HWND, UINT,WPARAM,LPARAM);
LRESULT CALLBACK WindowTermalEfficiencyCalc(HWND, UINT,WPARAM,LPARAM);


void AddControls(HWND);

void AddMechanics(HWND);
void AddFrictionCalc(HWND,LPARAM);
void AddInclinedPlaneCalc(HWND, LPARAM);
void AddFreeFallCalc(HWND);

void AddThermodynamics(HWND);
void AddEfficiencyCalc(HWND);
void AddIdealGasLawCalc(HWND);
void AddTermalEfficiencyCalc(HWND hWte);


HMENU hMenu;
HWND hFrictionCoef, hFrictionForce, hNormalForce, hEnergyInput, hEnergyOutput, hEfficiency,hComboBoxForce,
hComboBoxEnergyOutput, hComboBoxEnergyInput,hHeight,hInitialVelocity,hTimeOfFall,hVelocity, hComboBoxVelocity,
hComboBoxHeight, hMass, hComboBoxMass, hAngle, hComboBoxAngle, hResultingForce, hAcceleration,
hPressure, hVolume, hAmountOfSubstance,  hTemperature, hComboboxPressure, hComboboxVolume,
hColdTemperature;



int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst, LPSTR args, int ncmdshow){

    //create the main window with all the buttons for the physics chapters
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)){
        return -1;
    }

    CreateWindowW(L"myWindowClass", L"PHYSICS CALCULATORS", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 450, 50, 500, 525,NULL, NULL,NULL,NULL);
    

    //create the window for mechanics chapter
    WNDCLASSW wm = {0};

    wm.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wm.hCursor = LoadCursor(NULL,IDC_ARROW);
    wm.hInstance = hInst;
    wm.lpszClassName = L"MechanicsChoiceClass";
    wm.lpfnWndProc = WindowMechanics;

    if (!RegisterClassW(&wm)){
        return -1;
    }

    //create the window for friction calculator: mechanics
    WNDCLASSW fc = {0};

    fc.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    fc.hCursor = LoadCursor(NULL,IDC_ARROW);
    fc.hInstance = hInst;
    fc.lpszClassName = L"FrictionCalculatorClass";
    fc.lpfnWndProc = WindowFrictionCalc;

    if (!RegisterClassW(&fc)){
        return -1;
    }

    //create the window for inclined plane calculator: mechanics
    WNDCLASSW ic = {0};

    ic.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    ic.hCursor = LoadCursor(NULL,IDC_ARROW);
    ic.hInstance = hInst;
    ic.lpszClassName = L"InclinedPlaneCalculatorClass";
    ic.lpfnWndProc = WindowInclinedPlaneCalc;

    if (!RegisterClassW(&ic)){
        return -1;
    }

    //create the window for free fall calculator: mechanics
    WNDCLASSW ff = {0};

    ff.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    ff.hCursor = LoadCursor(NULL,IDC_ARROW);
    ff.hInstance = hInst;
    ff.lpszClassName = L"FreeFallCalculatorClass";
    ff.lpfnWndProc = WindowFreeFallCalc;

    if (!RegisterClassW(&ff)){
        return -1;
    }



    //create the window for the thermodynamics chapter
    WNDCLASSW wt = {0};

    wt.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    wt.hCursor = LoadCursor(NULL,IDC_ARROW);
    wt.hInstance = hInst;
    wt.lpszClassName = L"ThermodynamicsChoiceClass";
    wt.lpfnWndProc = WindowThermodynamics;

    if (!RegisterClassW(&wt)){
        return -1;
    }
    //create the window for Efficiency Calculator: thermodynamics
    WNDCLASSW ec = {0};

    ec.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    ec.hCursor = LoadCursor(NULL,IDC_ARROW);
    ec.hInstance = hInst;
    ec.lpszClassName = L"EfficiencyCalculatorClass";
    ec.lpfnWndProc = WindowEfficiencyCalc;

    if (!RegisterClassW(&ec)){
        return -1;
    }
    //create the window for Ideal Gas Law Calculator: thermodynamics
    WNDCLASSW ig = {0};

    ig.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    ig.hCursor = LoadCursor(NULL,IDC_ARROW);
    ig.hInstance = hInst;
    ig.lpszClassName = L"IdealGasLawCalculatorClass";
    ig.lpfnWndProc = WindowIdealGasLawCalc;

    if (!RegisterClassW(&ig)){
        return -1;
    }

    //create the window for Thermal Efficiency Calculator: thermodynamics
    WNDCLASSW te = {0};

    te.hbrBackground = (HBRUSH)COLOR_WINDOW ;
    te.hCursor = LoadCursor(NULL,IDC_ARROW);
    te.hInstance = hInst;
    te.lpszClassName = L"TermalEfficiencyCalculatorClass";
    te.lpfnWndProc = WindowTermalEfficiencyCalc;

    if (!RegisterClassW(&te)){
        return -1;
    }

    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg,WPARAM wp,LPARAM lp)
{
    switch (msg)
    {
        case WM_COMMAND:
        switch(wp){
            case MECHANICS_BUTTON:
                CreateWindowW(L"MechanicsChoiceClass", L"MECHANICS CALCULATORS", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 350, 10, 600, 650, NULL, NULL,NULL,NULL);
                break;
            case THERMODYNAMICS_BUTTON:
                CreateWindowW(L"ThermodynamicsChoiceClass", L"THERMODYNAMICS CALCULATORS", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 350, 10, 600, 650, NULL, NULL,NULL,NULL);
                break;
        }
        break;
        case WM_CREATE:
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp,lp);
    }

}


LRESULT CALLBACK WindowMechanics(HWND hWm, UINT msg,WPARAM wp,LPARAM lp)    //hWm - handler for Window [for] mechanics
{

    switch (msg)
    {
        case WM_COMMAND:
            switch(wp){
                case FRICTION_CALCULATOR:
                    CreateWindowW(L"FrictionCalculatorClass", L"FRICTION CALCULATOR", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 150, 100, 600, 600, NULL, NULL,NULL,NULL);
                    break;
                case INCLINED_PLANE_CALCULATOR:
                    CreateWindowW(L"InclinedPlaneCalculatorClass", L"INCLINED PLANE CALCULATOR", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 150, 100, 600, 650, NULL, NULL,NULL,NULL);
                    break;
                case FREE_FALL_CALCULATOR:
                    CreateWindowW(L"FreeFallCalculatorClass", L"FREE FALL CALCULATOR", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 350, 10, 600, 600, NULL, NULL,NULL,NULL);
                    break;
            }
            break;
        case WM_CREATE:
            AddMechanics(hWm);
            break;
        case WM_DESTROY:
            PostMessage(hWm, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWm, msg, wp,lp);

    }
    
}

LRESULT CALLBACK WindowFrictionCalc(HWND hWfc, UINT msg,WPARAM wp,LPARAM lp)   //hWfc - handler for Window [for] friction calc
{
    switch (msg)
    {   
        case WM_COMMAND: 
            switch (wp){
                case FRICTION_CALCULATOR_BUTTON:
                    HWND hComboBox = GetDlgItem(hWfc, COMBOBOX_FORCE);
                    int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

                    char force_unit[256];
                    
                    double normal_force = 0.0;
                    double friction_coef = 0.0;
                    double friction_force = 0.0;
                    char res[256];
                    
                    SendMessage(hComboBox,CB_GETLBTEXT,index, (LPARAM)force_unit);

                    if (!isvalidinput(hWfc, hFrictionCoef, &friction_coef, 1)){
                        //LOG(LOG_LEVEL_DEBUG, "User typed in incorrect value for friction coefficient. Friction Calculator");
                        break;
                    }

                    if (!isvalidinput(hWfc, hNormalForce, &normal_force, 1)){
                        //LOG(LOG_LEVEL_DEBUG, "User typed in incorrect value for normal force. Friction Calculator");
                        break;
                    }

                    // ConvertToSI(3, force_unit ,&normal_force, force, DoubleForce);
                    if (*force_unit==*force[1]){
                        normal_force *= DoubleForce[1];
                    }else if (*force_unit==*force[2]){
                        normal_force *= DoubleForce[2];
                    }
                    
                    friction_force = friction_coef*normal_force;

                    snprintf(res,sizeof(res),"%.10lf",friction_force);
                    SetWindowText(hFrictionForce, res);

                    break;
            }
            break;
        case WM_CREATE:
            AddFrictionCalc(hWfc, lp);
            break;
        case WM_DESTROY:
            PostMessage(hWfc, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWfc, msg, wp,lp);
    }
    
}

LRESULT CALLBACK WindowFreeFallCalc(HWND hWff, UINT msg, WPARAM wp,LPARAM lp){  //hWff - handler for Window [for] free fall calc
    switch (msg){
        case WM_COMMAND:
            switch(LOWORD(wp)){
                case 21:
                        int index_velocity = SendMessage(hComboBoxVelocity, CB_GETCURSEL, 0, 0);
                        int index_height = SendMessage(hComboBoxHeight, CB_GETCURSEL, 0, 0);

                        double initial_velocity = 0.0;
                        double height = 0.0;
                        double TimeOfFall= 0.0;
                        double velocity= 0.0;

                        char velocity_unit[256];
                        char height_unit[256];

                        SendMessage(hComboBoxVelocity,CB_GETLBTEXT,index_velocity, (LPARAM)velocity_unit);
                        SendMessage(hComboBoxHeight,CB_GETLBTEXT,index_height, (LPARAM)height_unit);

                        char res_time[256];
                        char res_velocity[256];

                        if(!isvalidinput(hWff, hInitialVelocity, &initial_velocity, 0) || !isvalidinput(hWff, hHeight, &height, 0)){
                            //LOG(LOG_LEVEL_DEBUG, "User typed in incorrect value . Free Fall Calculator");
                            break;
                        }

                        ConvertToSI(2, velocity_unit, &initial_velocity, Velocity, DoubleVelocity);
                        ConvertToSI(3, height_unit, &height, Height, DoubleHeight);

                        // Formula 

                        if (initial_velocity == 0){
                            TimeOfFall = sqrt((2*height)/g);
                            velocity = TimeOfFall*g;
                        }else{
                            TimeOfFall = (-initial_velocity+sqrt(pow(initial_velocity,2)+g*height))/g;
                            velocity = initial_velocity + g*TimeOfFall;
                        }
                        
                        snprintf(res_time,sizeof(res_time),"%.10lf",TimeOfFall);
                        snprintf(res_velocity,sizeof(res_velocity),"%.10lf",velocity); 
                        SetWindowText(hTimeOfFall, res_time);
                        SetWindowText(hVelocity, res_velocity);  
                        break;                     

                
            }
            break;
        case WM_CREATE:
            AddFreeFallCalc(hWff);
            break;
        case WM_DESTROY:
            PostMessage(hWff, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWff, msg, wp,lp);
    }
}

LRESULT CALLBACK WindowInclinedPlaneCalc(HWND hWip, UINT msg,WPARAM wp,LPARAM lp){    //hWip - handler for Window [for] inclined plane calculator 
    switch(msg){
        case WM_COMMAND:
            switch(LOWORD(wp)){
                case INCLINED_PLANE_CALCULATOR_BUTTON:
                    // 1 - getting info from comboboxes
                    int indexMass = SendMessage(hComboBoxMass, CB_GETCURSEL, 0, 0);
                    int indexAngle = SendMessage(hComboBoxAngle, CB_GETCURSEL, 0, 0);
                    int indexResultingForce = SendMessage(hComboBoxForce, CB_GETCURSEL, 0, 0);

                    // 2 - variables declaration

                    char mass_unit[256];
                    char angle_unit[256];
                    char force_unit[256];

                    double mass = 0.0;
                    double angle = 0.0;
                    double frictionCoef = 0.0;
                    double acceleration = 0.0;
                    double ResultingForce = 0.0;
                    double angle_of_friction = 0;

                    char ResultingForceChar[256];
                    char acceleration_char[256];

                    // Converting info from comboboxes to a char var
                    SendMessage(hComboBoxMass,CB_GETLBTEXT,indexMass, (LPARAM)mass_unit);
                    SendMessage(hComboBoxAngle,CB_GETLBTEXT,indexAngle, (LPARAM)angle_unit);
                    SendMessage(hComboBoxForce,CB_GETLBTEXT,indexResultingForce, (LPARAM)force_unit);

                    if (!isvalidinput(hWip, hMass, &mass, 0) || !isvalidinput(hWip, hAngle, &angle, 0) || !isvalidinput(hWip, hFrictionCoef, &frictionCoef, 0)){
                        //LOG(LOG_LEVEL_DEBUG, "User typed in incorrect value. Inclined Plane Calculator");
                        break;
                    }
                    
                    ConvertToSI(2, mass_unit, &mass, Mass, DoubleMass);
                    ConvertToSI(2, angle_unit, &angle, Angle, DoubleAngle);

                    if (angle>90){
                        MessageBoxW(hWip, L"Inclined plane angle should be lower than 90°.", L"Error", MB_OK);
                        SetWindowTextW(hResultingForce, L"0");
                        SetWindowTextW(hAcceleration, L"0");
                        break;
                    }

                    // Formulas

                    angle_of_friction = (atan(frictionCoef))*(180/M_PI);
                    if (angle <= angle_of_friction){
                        MessageBoxW(hWip, L"Object will not move, all forces are compensated", L"Error", MB_OK);
                        // Show user acceleration = 0, resulting_force = 0
                        SetWindowTextW(hResultingForce, L"0");
                        SetWindowTextW(hAcceleration, L"0");
                        break;
                    }

                    double gravitational_force = mass * g;
                    double f_i = gravitational_force * sin(angle/(180/M_PI));
                    double f_n = gravitational_force * cos(angle/(180/M_PI));
                    double force_of_friction = f_n * frictionCoef;

                    ResultingForce = f_i - force_of_friction;
                    acceleration = ResultingForce/mass;

                    // Taking into account unit for resulting force
                    for (int i=0; i < 2; ++i){
                        if (*force_unit == *force[i]){
                            ResultingForce = ResultingForce / DoubleForce[i];

                        }
                    }
                    
                    snprintf(ResultingForceChar,sizeof(ResultingForceChar),"%.10lf",ResultingForce);
                    snprintf(acceleration_char,sizeof(acceleration_char),"%.10lf",acceleration);

                    SetWindowText(hAcceleration, acceleration_char);
                    SetWindowText(hResultingForce, ResultingForceChar);

                    break;
            }
            break;
        case WM_CREATE:
            AddInclinedPlaneCalc(hWip, lp);
            break;
        case WM_DESTROY:
            PostMessage(hWip, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWip, msg, wp,lp);
    }
}


LRESULT CALLBACK WindowThermodynamics(HWND hWt, UINT msg,WPARAM wp,LPARAM lp)    //hWt - handler for Window [for] thermodynamics
{
    switch (msg)
    {
        case WM_COMMAND:
            switch(wp){
                case EFFICIENCY_CALCULATOR:
                    CreateWindowW(L"EfficiencyCalculatorClass", L"EFFICIENCY CALCULATOR", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 150, 100, 600, 600, NULL, NULL,NULL,NULL);
                    break;
                case IDEAL_GAS_LAW_CALCULATOR:
                    CreateWindowW(L"IdealGasLawCalculatorClass", L"IDEAL GAS LAW CALCULATOR", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 350, 10, 600, 700, NULL, NULL,NULL,NULL);
                    break;
                case THERMAL_EFFICIENCY_CALCULATOR:
                    CreateWindowW(L"TermalEfficiencyCalculatorClass", L"TERMAL EFFICIENCY CALCULATOR", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 350, 10, 600, 425, NULL, NULL,NULL,NULL);
                    break;
            }
            break;
        case WM_CREATE:
            AddThermodynamics(hWt);
            break;
        case WM_DESTROY:
            PostMessage(hWt, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWt, msg, wp,lp);

    }
    
}

LRESULT CALLBACK WindowEfficiencyCalc(HWND hWec, UINT msg,WPARAM wp,LPARAM lp)    //hWec - handler for Window [for] efficiency calculator
{
    switch (msg)
    {
        case WM_COMMAND:
            switch(wp){
                case EFFICIENCY_CALCULATOR_BUTTON:
                    // getting info from comboboxes
                    
                    HWND hComboBoxEnergyInput = GetDlgItem(hWec, COMBOBOX_ENERGY_INPUT);
                    int index = SendMessage(hComboBoxEnergyInput, CB_GETCURSEL, 0, 0);

                    HWND hComboBoxEnergyOutput = GetDlgItem(hWec, COMBOBOX_ENERGY_OUTPUT);
                    int NextIndex = SendMessage(hComboBoxEnergyOutput, CB_GETCURSEL, 0, 0);

                    char energy_unit_input[256];
                    char energy_unit_output[256];

                    double energy_input = 0.0;
                    double energy_output = 0.0;
                    double efficiency = 0.0;

                    char res[256];
                    
                    // Converting info from comboboxes to a char var
                    SendMessage(hComboBoxEnergyInput,CB_GETLBTEXT,index, (LPARAM)energy_unit_input);
                    SendMessage(hComboBoxEnergyOutput,CB_GETLBTEXT,NextIndex, (LPARAM)energy_unit_output);

                    if (!isvalidinput(hWec, hEnergyInput, &energy_input, 1)){
                        break;
                    }

                    if (!isvalidinput(hWec, hEnergyOutput, &energy_output, 1)){
                        break;
                    }

                    ConvertToSI(5, energy_unit_input, &energy_input, energy, DoubleEnergy);
                    ConvertToSI(5, energy_unit_output, &energy_output, energy, DoubleEnergy);

                    // Formula
                    efficiency = (energy_output/energy_input)*100;

                    snprintf(res,sizeof(res),"%.10lf",efficiency);
                    SetWindowText(hEfficiency, res);
                    break;
            }
            break;
        case WM_CREATE:
            AddEfficiencyCalc(hWec);
            break;
        case WM_DESTROY:
            PostMessage(hWec, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWec, msg, wp,lp);

    }
    
}

LRESULT CALLBACK WindowIdealGasLawCalc(HWND hWig, UINT msg,WPARAM wp,LPARAM lp){          //hWig - handler for Window [for] ideal gas law calculator 
    switch(msg){
        case WM_COMMAND:
            // Variables declaration
                double amount_of_substance = 0;
                double volume = 0;
                double pressure = 0;
                double temperature = 0;
                char pressureChar[256];
                char volumeChar[256];
                char amountOfSubstanceChar[256];
                char temperatureChar[256];
                char pressure_unit[256];
                char volume_unit[256];
                char buffer1[256], buffer2[256], buffer3[256];
                char res[256];
            switch(LOWORD(wp)){                
                case 201://pressure
                    GetWindowText(hVolume, buffer1, sizeof(buffer1));
                    GetWindowText(hAmountOfSubstance, buffer2, sizeof(buffer2));
                    GetWindowText(hTemperature, buffer3, sizeof(buffer3));
                    // Checking if there is input in three edit fields
                    if (strlen(buffer1)> 0 && strlen(buffer2)> 0 && strlen(buffer3)> 0){
                        int indexPressure = SendMessage(hComboboxPressure, CB_GETCURSEL, 0, 0);
                        int indexVolume = SendMessage(hComboboxVolume, CB_GETCURSEL, 0, 0);
                        // Converting info from comboboxes to a char var
                        SendMessage(hComboboxPressure,CB_GETLBTEXT,indexPressure, (LPARAM)pressure_unit);
                        SendMessage(hComboboxVolume,CB_GETLBTEXT,indexVolume, (LPARAM)volume_unit);
                        if (!isvalidinput(hWig, hVolume, &volume, 0) || !isvalidinput(hWig, hAmountOfSubstance, &amount_of_substance, 0) || !isvalidinput(hWig, hTemperature, &temperature, 1)){
                            break;
                            }
                        ConvertToSI(5, volume_unit, &volume, Volume, DoubleVolume);
                         //Also converting temperature to Kelvin
                        temperature = temperature + 273.15;
                        if( temperature<=0){
                            MessageBoxW(hWig, L"Temperature cannot reach or drop below absolute zero (0 K or -278℃).", L"Error", MB_ICONERROR);
                        break;
                        }
                        // Formula
                        pressure = (amount_of_substance *  temperature * R)/volume;
                        
                        for (int i=0; i<4; ++i){
                            if (*pressure_unit==*Pressure[i]){
                                pressure = pressure / DoublePressure[i];
                            }
                        }
                        snprintf(res,sizeof(res),"%.10lf",pressure);
                        SetWindowText(hPressure, res);
                        
                    }
                    amount_of_substance = 0;
                    volume = 0;
                    pressure = 0;
                    temperature = 0;
                    
                    break;
                case 202://volume
                    GetWindowText(hPressure, buffer1, sizeof(buffer1));
                    GetWindowText(hAmountOfSubstance, buffer2, sizeof(buffer2));
                    GetWindowText(hTemperature, buffer3, sizeof(buffer3));
                    // Checking if there is input in three edit fields
                    if (strlen(buffer1)> 0 && strlen(buffer2)> 0 && strlen(buffer3)> 0){
                        amount_of_substance = 0;
                        volume = 0;
                        pressure = 0;
                        temperature = 0;
                        int indexPressure = SendMessage(hComboboxPressure, CB_GETCURSEL, 0, 0);
                        int indexVolume = SendMessage(hComboboxVolume, CB_GETCURSEL, 0, 0);
                        // Converting info from comboboxes to a char var
                        SendMessage(hComboboxPressure,CB_GETLBTEXT,indexPressure, (LPARAM)pressure_unit);
                        SendMessage(hComboboxVolume,CB_GETLBTEXT,indexVolume, (LPARAM)volume_unit);
                        if (!isvalidinput(hWig, hPressure, &pressure, 0) || !isvalidinput(hWig, hAmountOfSubstance, &amount_of_substance, 0) || !isvalidinput(hWig, hTemperature, &temperature, 1)){
                            break;
                            }
                        ConvertToSI(4, pressure_unit, &pressure, Pressure, DoublePressure);
                        // Also converting temperature to Kelvins
                        temperature += 273.15;
                        if( temperature<=0){
                            MessageBoxW(hWig, L"Temperature cannot reach or drop below absolute zero (0 K or -278℃).", L"Error", MB_ICONERROR);
                        break;
                        }
                        // Formula
                        volume = (amount_of_substance *  temperature * R)/pressure;

                        for (int i=0; i<5; ++i){
                            if (*volume_unit==*Volume[i]){
                                volume = volume/ DoubleVolume[i];
                            }
                        }
                        snprintf(buffer1,sizeof(buffer1),"%.10lf",volume);
                        SetWindowText(hVolume, buffer1);
                    }
                    
                    break;
                case 203://amount of substance
                    GetWindowText(hPressure, buffer1, sizeof(buffer1));
                    GetWindowText(hVolume, buffer2, sizeof(buffer2));
                    GetWindowText(hTemperature, buffer3, sizeof(buffer3));
                    // Checking if there is input in two edit fields
                    if (strlen(buffer1)> 0 && strlen(buffer2)> 0 && strlen(buffer3)> 0){
                        amount_of_substance = 0;
                        volume = 0;
                        pressure = 0;
                        temperature = 0;
                        int indexPressure = SendMessage(hComboboxPressure, CB_GETCURSEL, 0, 0);
                        int indexVolume = SendMessage(hComboboxVolume, CB_GETCURSEL, 0, 0);
                        // Converting info from comboboxes to a char var
                        SendMessage(hComboboxPressure,CB_GETLBTEXT,indexPressure, (LPARAM)pressure_unit);
                        SendMessage(hComboboxVolume,CB_GETLBTEXT,indexVolume, (LPARAM)volume_unit);
                        if (!isvalidinput(hWig, hPressure, &pressure, 0) || !isvalidinput(hWig, hVolume, &volume, 0) || !isvalidinput(hWig, hTemperature, &temperature, 1)){
                            break;
                            }
                        ConvertToSI(4, pressure_unit, &pressure, Pressure, DoublePressure);
                        ConvertToSI(5, volume_unit, &volume, Volume, DoubleVolume);
                        // Also converting temperature to Kelvins
                        temperature += 273.15;
                        if( temperature<=0){
                            MessageBoxW(hWig, L"Temperature cannot reach or drop below absolute zero (0 K or -278℃).", L"Error", MB_ICONERROR);
                        break;
                        }
                        // Formula
                        amount_of_substance  = pressure*volume/(temperature * R);
                        
                        snprintf(buffer1,sizeof(buffer1),"%.10lf",amount_of_substance);
                        SetWindowText(hAmountOfSubstance, buffer1);
                    }

                    break;
                case 204://temperature
                    GetWindowText(hPressure, buffer1, sizeof(buffer1));
                    GetWindowText(hVolume, buffer2, sizeof(buffer2));
                    GetWindowText(hAmountOfSubstance, buffer3, sizeof(buffer3));
                    // Checking if there is input in three edit fields
                    if (strlen(buffer1)> 0 && strlen(buffer2)> 0 && strlen(buffer3)> 0){
                        amount_of_substance = 0;
                        volume = 0;
                        pressure = 0;
                        temperature = 0;
                        int indexPressure = SendMessage(hComboboxPressure, CB_GETCURSEL, 0, 0);
                        int indexVolume = SendMessage(hComboboxVolume, CB_GETCURSEL, 0, 0);
                        // Converting info from comboboxes to a char var
                        SendMessage(hComboboxPressure,CB_GETLBTEXT,indexPressure, (LPARAM)pressure_unit);
                        SendMessage(hComboboxVolume,CB_GETLBTEXT,indexVolume, (LPARAM)volume_unit);
                        if (!isvalidinput(hWig, hPressure, &pressure, 0) || !isvalidinput(hWig, hVolume, &volume, 0) || !isvalidinput(hWig, hAmountOfSubstance, &amount_of_substance, 0)){
                            break;
                            }
                        ConvertToSI(4, pressure_unit, &pressure, Pressure, DoublePressure);
                        ConvertToSI(5, volume_unit, &volume, Volume, DoubleVolume);
                        
                        // Formula
                        temperature  = pressure*volume/(amount_of_substance* R);
                        // Converting temperature from Kelvin to Celcius
                        temperature -= 273.15;
                        
                        snprintf(buffer1,sizeof(buffer1),"%.10lf",temperature);
                        SetWindowText(hTemperature, buffer1);
                    }
                    
                    break;
                case 205:
                    MessageBoxW(hWig, L"Enter all the values besides that one you want to find", L"Instruction", MB_ICONINFORMATION);
                    break;
            }
            break;
        case WM_CREATE:
            AddIdealGasLawCalc(hWig);
            break;
        case WM_DESTROY:
            PostMessage(hWig, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWig, msg, wp,lp);
    }
}

LRESULT CALLBACK WindowTermalEfficiencyCalc(HWND hWte, UINT msg,WPARAM wp,LPARAM lp){   //hWte - handler for Window [for] termal efficiency calc
    switch(msg){
        case WM_COMMAND:
            switch(LOWORD(wp)){
                case 301:
                case 302:
                if (HIWORD(wp) == EN_CHANGE){
                    char buffer1[256], buffer2[256];
                    GetWindowText(hTemperature, buffer1, sizeof(buffer1));
                    GetWindowText(hColdTemperature, buffer2, sizeof(buffer2));
                    // Checking if there is input in two edit fields
                    if (strlen(buffer1)> 0 && strlen(buffer2)> 0 ){
                    double hot_t = 0.0;
                    double cold_t = 0.0;
                    double efficiency = 0.0;
                    char efficiencychar[256];

                    if (!isvalidinput(hWte, hTemperature, &hot_t, 1) || !isvalidinput(hWte, hColdTemperature, &cold_t, 1)){
                        //LOG(LOG_LEVEL_DEBUG, "User typed in incorrect value .Termal Efficiency Calculator");
                        break;
                    }

                    // Checking if hot temp is greater than cold
                    if (hot_t <= cold_t){
                        SetWindowTextW(hEfficiency, L"0");
                        MessageBoxW(hWte, L"Hot temperature must be higher than cold one for heat transef to occur", L"Error", MB_ICONERROR);
                        break;
                    }
                    // Converting temperature from Celcius to Kelvin
                    hot_t += 273.15;
                    cold_t += 273.15;

                    if (hot_t<=0 || cold_t <=0){
                        SetWindowTextW(hEfficiency, L"0");
                        MessageBoxW(hWte, L"Temperature cannot reach or drop below absolute zero (0 K or -278℃).", L"Error", MB_ICONERROR);
                        break;
                    }

                    // Formulas
                    efficiency = (1 - cold_t/hot_t)*100;
                    snprintf(efficiencychar, sizeof(efficiencychar), "%.10lf",efficiency);
                    SetWindowText(hEfficiency, efficiencychar);
                    }}
                    break;
                case 303:
                    //LOG(LOG_LEVEL_INFO, "User clicked on 'INFO' button while using Termal Efficiency Calculator");
                    MessageBoxW(hWte, L"Type in the hot and cold temperatures and get a thermal efficiency.", L"INFO", MB_ICONINFORMATION);
                    break;
            }
            break;
        case WM_CREATE:
            AddTermalEfficiencyCalc(hWte);
            break;
        case WM_DESTROY:
            PostMessage(hWte, WM_CLOSE, 0, 0);
            break;
        default:
            return DefWindowProcW(hWte, msg, wp,lp);
    }
}


void AddControls(HWND hWnd){
    CreateWindowW(L"Button", L"Mechanics", WS_VISIBLE | WS_CHILD,50,25,400,200,hWnd,(HMENU)MECHANICS_BUTTON,NULL,NULL);
    CreateWindowW(L"Button", L"Thermodynamics", WS_VISIBLE | WS_CHILD,50,250,400,200,hWnd,(HMENU)THERMODYNAMICS_BUTTON,NULL,NULL);
}

void AddMechanics(HWND hWm){
    CreateWindowW(L"Button", L"Friction Calculator", WS_VISIBLE | WS_CHILD,50,37.5,500,150,hWm,(HMENU)FRICTION_CALCULATOR,NULL,NULL);
    CreateWindowW(L"Button", L"Inclined Plane Calculator", WS_VISIBLE | WS_CHILD,50,225,500,150,hWm,(HMENU)INCLINED_PLANE_CALCULATOR,NULL,NULL);
    CreateWindowW(L"Button", L"Free Fall Calculator", WS_VISIBLE | WS_CHILD,50,412.5,500,150,hWm,(HMENU)FREE_FALL_CALCULATOR,NULL,NULL);

}

void AddFrictionCalc(HWND hWfc, LPARAM lp){
    CreateWindowW(L"Static", L"Friction coefficient",WS_VISIBLE | WS_CHILD, 75, 15, 450, 40, hWfc, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Normal force",WS_VISIBLE | WS_CHILD, 75, 190, 450, 40, hWfc, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Friction force",WS_VISIBLE | WS_CHILD, 75, 365, 450, 40, hWfc, NULL, NULL, NULL);
    
    hFrictionCoef = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 75, 75, 400, 100, hWfc, NULL, NULL, NULL);
    hNormalForce = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 75, 250, 400, 100, hWfc, NULL, NULL, NULL);
    //combobox
    hComboBoxForce = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    475, 250, 100, 100, hWfc, (HMENU)COMBOBOX_FORCE, NULL, NULL);
    SendMessage(GetDlgItem(hWfc,COMBOBOX_FORCE),CB_ADDSTRING, 0, (LPARAM)"Newtons");
    SendMessage(GetDlgItem(hWfc,COMBOBOX_FORCE),CB_ADDSTRING, 0, (LPARAM)"Kilonewtons");
    SendMessage(GetDlgItem(hWfc,COMBOBOX_FORCE),CB_ADDSTRING, 0, (LPARAM)"Meganewtons");
    SendMessage(hComboBoxForce, CB_SETCURSEL, 0, 0);
    CreateWindowW(L"Button", L"Friction Force", WS_VISIBLE | WS_CHILD | WS_BORDER , 75, 425, 150, 100, hWfc, (HMENU)FRICTION_CALCULATOR_BUTTON, NULL, NULL);
    hFrictionForce = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 245, 425, 280, 100, hWfc, NULL, NULL, NULL);
    

}

void AddInclinedPlaneCalc(HWND hWip, LPARAM lp){
    CreateWindowW(L"Static", L"Object: ", WS_VISIBLE | WS_CHILD, 50, 50, 150, 50, hWip, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Cubic block", WS_VISIBLE | WS_CHILD, 300, 50, 250, 50, hWip, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Mass", WS_VISIBLE | WS_CHILD, 50, 125, 500, 25, hWip, NULL, NULL, NULL);
    hMass = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 150, 350, 50, hWip, (HMENU)31, NULL, NULL);
    hComboBoxMass = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    450, 150, 100, 100, hWip, (HMENU)COMBOBOX_MASS, NULL, NULL);
    SendMessage(GetDlgItem(hWip,COMBOBOX_MASS),CB_ADDSTRING, 0, (LPARAM)"Grams");
    SendMessage(GetDlgItem(hWip,COMBOBOX_MASS),CB_ADDSTRING, 0, (LPARAM)"Kilograms");
    SendMessage(hComboBoxMass, CB_SETCURSEL, 1, 0);

    CreateWindowW(L"Static", L"ANGLE", WS_VISIBLE | WS_CHILD, 50, 225, 500, 25, hWip, NULL, NULL, NULL);
    hAngle = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 250, 350, 50, hWip, (HMENU)32, NULL, NULL);
    hComboBoxAngle = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    450, 250, 100, 100, hWip, (HMENU)COMBOBOX_ANGLE, NULL, NULL);
    SendMessage(GetDlgItem(hWip,COMBOBOX_ANGLE),CB_ADDSTRING, 0, (LPARAM)"Degrees");
    SendMessage(GetDlgItem(hWip,COMBOBOX_ANGLE),CB_ADDSTRING, 0, (LPARAM)"Radians");
    SendMessage(hComboBoxAngle, CB_SETCURSEL, 0, 0);
    

    CreateWindowW(L"Static", L"Friction coefficient", WS_VISIBLE | WS_CHILD, 50, 325, 500, 25, hWip, NULL, NULL, NULL);
    hFrictionCoef = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 350, 500, 50, hWip, (HMENU)33, NULL, NULL);

    // Results
    CreateWindowW(L"Static", L"RESULTING FORCE", WS_VISIBLE | WS_CHILD , 75, 465, 150, 50, hWip, NULL, NULL, NULL);
    hResultingForce = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 225, 450, 150, 50, hWip, (HMENU)34, NULL, NULL);
    hComboBoxForce = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    400, 450, 100, 100, hWip, (HMENU)101, NULL, NULL);
    SendMessage(hComboBoxForce,CB_ADDSTRING, 0, (LPARAM)"Newtons");
    SendMessage(hComboBoxForce,CB_ADDSTRING, 0, (LPARAM)"Kilonewtons");
    SendMessage(hComboBoxForce, CB_SETCURSEL, 0, 0);

    CreateWindowW(L"Static", L"ACCELERATION", WS_VISIBLE | WS_CHILD, 75, 565, 150, 50, hWip, NULL, NULL, NULL);
    hAcceleration = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 225, 550, 150, 50, hWip, (HMENU)35, NULL, NULL);
    CreateWindowW(L"Static", L"M/S²", WS_VISIBLE | WS_CHILD, 425, 550, 100, 50, hWip, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"CALCULATE", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 505, 150, 40, hWip, (HMENU)INCLINED_PLANE_CALCULATOR_BUTTON, NULL, NULL);


}

void AddFreeFallCalc(HWND hWff){
    CreateWindowW(L"Static", L"Initial velocity",WS_VISIBLE | WS_CHILD, 50, 25, 400, 25, hWff, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Height",WS_VISIBLE | WS_CHILD, 50, 125, 400, 25, hWff, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"CALCULATE", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 250, 150, 30, hWff, (HMENU)21, NULL, NULL);
    //CreateWindowW(L"Static", L"Time of fall",WS_VISIBLE | WS_CHILD, 50, 250, 400, 25, hWff, NULL, NULL, NULL);
    //CreateWindowW(L"Static", L"Velocity",WS_VISIBLE | WS_CHILD, 50, 375, 400, 25, hWff, NULL, NULL, NULL);

    hInitialVelocity = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_GROUP| WS_TABSTOP , 50, 75, 400, 50, hWff, (HMENU)41, NULL, NULL);
    hHeight = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_GROUP | WS_TABSTOP, 50, 175, 400, 50, hWff, (HMENU)42, NULL, NULL);
    hTimeOfFall = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 275, 300, 250, 50, hWff, NULL, NULL, NULL);
    hVelocity = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 275, 425, 250, 50, hWff, NULL, NULL, NULL);

    //combobox for velocity
    hComboBoxVelocity = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    450, 75, 100, 100, hWff, (HMENU)COMBOBOX_VELOCITY, NULL, NULL);
    SendMessage(GetDlgItem(hWff,COMBOBOX_VELOCITY),CB_ADDSTRING, 0, (LPARAM)"M/s");
    SendMessage(GetDlgItem(hWff,COMBOBOX_VELOCITY),CB_ADDSTRING, 0, (LPARAM)"Km/h");
    SendMessage(hComboBoxVelocity, CB_SETCURSEL, 0, 0);
    
    //combobox for height
    hComboBoxHeight = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    450, 175, 100, 100, hWff, (HMENU)COMBOBOX_HEIGHT, NULL, NULL);
    SendMessage(hComboBoxHeight,CB_ADDSTRING, 0, (LPARAM)"Cm");
    SendMessage(hComboBoxHeight,CB_ADDSTRING, 0, (LPARAM)"M");
    SendMessage(hComboBoxHeight,CB_ADDSTRING, 0, (LPARAM)"Km");
    SendMessage(hComboBoxHeight, CB_SETCURSEL, 1, 0);

    
    CreateWindowW(L"Static", L"TIME OF FALL (s)", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 50, 300, 200, 50, hWff, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"VELOCITY (m/s)", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 50, 425, 200, 50, hWff, NULL, NULL, NULL);
    
}

void AddThermodynamics(HWND hWt){
    CreateWindowW(L"Button", L"Efficiency Calculator", WS_VISIBLE | WS_CHILD,50,37.5,500,150,hWt,(HMENU)EFFICIENCY_CALCULATOR,NULL,NULL);
    CreateWindowW(L"Button", L"Ideal Gas Law Calculator", WS_VISIBLE | WS_CHILD,50,225,500,150,hWt,(HMENU)IDEAL_GAS_LAW_CALCULATOR,NULL,NULL);
    CreateWindowW(L"Button", L"Thermal Efficiency Calculator", WS_VISIBLE | WS_CHILD,50,412.5,500,150,hWt,(HMENU)THERMAL_EFFICIENCY_CALCULATOR,NULL,NULL);

}

void AddEfficiencyCalc(HWND hWec){
    CreateWindowW(L"Static", L"Energy input",WS_VISIBLE | WS_CHILD, 75, 15, 450, 40, hWec, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Energy output",WS_VISIBLE | WS_CHILD, 75, 190, 450, 40, hWec, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Efficiency(%)",WS_VISIBLE | WS_CHILD, 75, 365, 450, 40, hWec, NULL, NULL, NULL);

    //combobox 1 for energy_input
    hComboBoxEnergyInput = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    480, 75, 100, 150, hWec, (HMENU)COMBOBOX_ENERGY_INPUT, NULL, NULL);
    SendMessage(GetDlgItem(hWec,COMBOBOX_ENERGY_INPUT),CB_ADDSTRING, 0, (LPARAM)"Joules");
    SendMessage(GetDlgItem(hWec,COMBOBOX_ENERGY_INPUT),CB_ADDSTRING, 0, (LPARAM)"Kilojoules");
    SendMessage(GetDlgItem(hWec,COMBOBOX_ENERGY_INPUT),CB_ADDSTRING, 0, (LPARAM)"Megajoules");
    SendMessage(GetDlgItem(hWec,COMBOBOX_ENERGY_INPUT),CB_ADDSTRING, 0, (LPARAM)"Watt hours");
    SendMessage(GetDlgItem(hWec,COMBOBOX_ENERGY_INPUT),CB_ADDSTRING, 0, (LPARAM)"Kilowatt hours");
    SendMessage(hComboBoxEnergyInput, CB_SETCURSEL, 0, 0);
   
    //combobox 2 for energy_output
    hComboBoxEnergyOutput = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    480, 250, 100, 150, hWec, (HMENU)COMBOBOX_ENERGY_OUTPUT, NULL, NULL);
    SendMessage(hComboBoxEnergyOutput,CB_ADDSTRING, 0, (LPARAM)"Joules");
    SendMessage(hComboBoxEnergyOutput,CB_ADDSTRING, 0, (LPARAM)"Kilojoules");
    SendMessage(hComboBoxEnergyOutput,CB_ADDSTRING, 0, (LPARAM)"Megajoules");
    SendMessage(hComboBoxEnergyOutput,CB_ADDSTRING, 0, (LPARAM)"Watt hours");
    SendMessage(hComboBoxEnergyOutput,CB_ADDSTRING, 0, (LPARAM)"Kilowatt hours");
    SendMessage(hComboBoxEnergyOutput, CB_SETCURSEL, 0, 0);


    hEnergyInput = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 75, 75, 400, 100, hWec, NULL, NULL, NULL);
    hEnergyOutput = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 75, 250, 400, 100, hWec, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"Efficiency", WS_VISIBLE | WS_CHILD | WS_BORDER , 75, 425, 150, 100, hWec, (HMENU)EFFICIENCY_CALCULATOR_BUTTON, NULL, NULL);
    hEfficiency = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 245, 425, 280, 100, hWec, NULL, NULL, NULL);
}

void AddIdealGasLawCalc(HWND hWig){
    // Static fields
    CreateWindowW(L"Static", L"Pressure",WS_VISIBLE | WS_CHILD, 50, 25, 150, 25, hWig, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Volume",WS_VISIBLE | WS_CHILD, 50, 175, 150, 25, hWig, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Amount of substance (mol)",WS_VISIBLE | WS_CHILD, 50, 325, 175, 25, hWig, NULL, NULL, NULL);
    //CreateWindowW(L"Static", L"m",WS_VISIBLE | WS_CHILD, 400, 350, 50, 50, hWig, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Temperature (℃)",WS_VISIBLE | WS_CHILD, 50, 475, 150, 25, hWig, NULL, NULL, NULL);
    //CreateWindowW(L"Static", L"",WS_VISIBLE | WS_CHILD, 400, 500, 50, 50, hWig, NULL, NULL, NULL);
    // Edit fields
    hPressure = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 50, 300, 75, hWig, NULL, NULL, NULL);
    hVolume = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 200, 300, 75, hWig, NULL, NULL, NULL);
    hAmountOfSubstance = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 350, 300, 75, hWig, NULL, NULL, NULL);
    hTemperature = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 500, 300, 75, hWig, NULL, NULL, NULL);
    // Buttons
    CreateWindowW(L"Button", L"Find\n Pressure", WS_VISIBLE | WS_CHILD | WS_BORDER |BS_MULTILINE, 475, 50, 100, 100, hWig, (HMENU)201, NULL, NULL);
    CreateWindowW(L"Button", L"Find\n Volume", WS_VISIBLE | WS_CHILD | WS_BORDER |BS_MULTILINE, 475, 200, 100, 100, hWig, (HMENU)202, NULL, NULL);
    CreateWindowW(L"Button", L"Find\n Amount of substance", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_MULTILINE, 475, 350, 100, 100, hWig, (HMENU)203, NULL, NULL);
    CreateWindowW(L"Button", L"Find\n Temperature", WS_VISIBLE | WS_CHILD | WS_BORDER | BS_MULTILINE, 475, 500, 100, 100, hWig, (HMENU)204, NULL, NULL);
    CreateWindowW(L"Button", L"     How to use      ", WS_VISIBLE | WS_CHILD | WS_BORDER , 50, 600, 300, 50, hWig, (HMENU)205, NULL, NULL);
    //Comboboxes
    hComboboxPressure = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    350, 50, 125, 150, hWig, (HMENU)206, NULL, NULL);
    //"Pascals(Pa)", "Kilopascals(kPa)", "Megapascals(MPa)", "Bars(bar)"
    SendMessage(hComboboxPressure,CB_ADDSTRING, 0, (LPARAM)"Pascals(Pa)");
    SendMessage(hComboboxPressure,CB_ADDSTRING, 0, (LPARAM)"Kilopascals(kPa)");
    SendMessage(hComboboxPressure,CB_ADDSTRING, 0, (LPARAM)"Megapascals(MPa)");
    SendMessage(hComboboxPressure,CB_ADDSTRING, 0, (LPARAM)"Bars(bar)");
    SendMessage(hComboboxPressure, CB_SETCURSEL, 0, 0); 

    hComboboxVolume = CreateWindowW(L"COMBOBOX",L"CHOOSE UNIT", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
    350, 200, 125, 150, hWig, (HMENU)207, NULL, NULL);
    //"Pascals(Pa)", "Kilopascals(kPa)", "Megapascals(MPa)", "Bars(bar)"
    SendMessage(hComboboxVolume,CB_ADDSTRING, 0, (LPARAM)"Cubic milimeters(mm^3)");
    SendMessage(hComboboxVolume,CB_ADDSTRING, 0, (LPARAM)"Cubic cantimeters(cm^3)");
    SendMessage(hComboboxVolume,CB_ADDSTRING, 0, (LPARAM)"Cubic meters(m^3)");
    SendMessage(hComboboxVolume,CB_ADDSTRING, 0, (LPARAM)"Mililiters(ml)");
    SendMessage(hComboboxVolume,CB_ADDSTRING, 0, (LPARAM)"Liters(l)");
    SendMessage(hComboboxVolume, CB_SETCURSEL, 2, 0); 


}

void AddTermalEfficiencyCalc(HWND hWte){
    CreateWindowW(L"Static", L"Hot reservoir temperature (℃)",WS_VISIBLE | WS_CHILD, 50, 25, 150, 250, hWte, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Cold reservoir temperature (℃)",WS_VISIBLE | WS_CHILD, 50, 150, 150, 50, hWte, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Termal efficiency(%)",WS_VISIBLE | WS_CHILD, 50, 275, 150, 50, hWte, NULL, NULL, NULL);
    hTemperature = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 275, 25, 150, 50, hWte, (HMENU)301, NULL, NULL);
    hColdTemperature = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 275, 150, 150, 50, hWte,(HMENU)302, NULL, NULL);
    hEfficiency = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER , 275, 275, 150, 50, hWte, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"INFO", WS_VISIBLE | WS_CHILD | WS_BORDER , 275, 340, 100, 30, hWte, (HMENU)303, NULL, NULL);
}
