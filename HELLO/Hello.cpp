#include <stdio.h>
#include <iostream>
using namespace std;

int main(void){
    cout<<"Hello world\n";
    return(0);
}

template <typename t>

class matrix
{

Public:

        //default constructor
        matrix(); 
        
        // overloaded constructor
        matrix(std:ifstream&, const char*);

        // copy constructor
        matrix(const matrix&); 
        
        // destructor
        ~matrix(); 
        
        //operator overloads
        T* operator [](T);
        const matrix operator* (const matrix&) const;
        matrix& operator = (const matrix&);
        friend std::ostream& operator<< <T> (std::ostream&, const matrix<T>&);

Private:
        t** the_matrix;
        unsigned rows, cols;
}


