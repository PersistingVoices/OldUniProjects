#include<stdio.h>
#include<iostream>
using namespace std;

void swap(int &x, int &y)
{
    int temp;
    temp = x; /* save the value at address x */
    x = y;    /* put y into x */
    y = temp; /* put x into y */

    return;
}

// function declaration
void swap(int &x, int &y);


int main ()
{
    // local variable declaration:
    int a = 100;
    int b = 200;
    
    cout << "\n\n------------Finding the MAX-----------\n\n"<< endl;
    cout << "Please enter the value of a :"  << endl;
    cin >>  a;
    cout << endl;
    cout << "Please enter the value of b :"  << endl;
    cin >>  b;
    cout << endl;

    /* calling a function to swap the values using variable reference.*/
    swap(a, b);

    cout<<"After Swap:"<< endl;
    cout << "a :" << a << endl;
    cout << "b :" << b << endl;

    return 0;
}
