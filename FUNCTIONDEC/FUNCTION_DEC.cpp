#include <iostream>
#include <stdio.h>
using namespace std;

//function declaration
int max(int num1, int num2);

int main ()
{
    // local variable declaration:
    int a;
    int b;
    int ret;

    cout << "\n\n------------Finding the MAX-----------"<< endl;
    cout << "Please enter the value of a :"  << endl;
    cin >>  a;
    cout << endl;
    cout << "Please enter the value of b :"  << endl;
    cin >>  b;
    cout << endl;
    // calling a function to get max value.
    ret = max(a, b);

    cout << "Max value is : " << ret << endl;
    cout << endl;
    return 0;
}


// function returning the max between two numbers
int max(int num1, int num2) 
{
    // local variable declaration
    int result;

    if (num1 > num2)
        result = num1;
    else
        result = num2;

    return result; 
}

