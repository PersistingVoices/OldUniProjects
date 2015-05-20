#include <iostream>
using namespace std;

class A
{
    public:
       void fetchClassName() {  cout<< "A"<<endl; }
};

class B: public A
{
    public:
        void fetchClassName() {  cout<< "B"<<endl; }
};

void print_stuff(A *aa){ aa->fetchClassName();}

int main(void)
{
    A *a = new A;
    B *b = new B;

    cout << "\nWhen there are no virtual functions implimeted, and B's (child class) function is called: \n\nThe following Class is accessed\n"<<endl;

    print_stuff(b);
}
