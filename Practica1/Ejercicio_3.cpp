#include<bits/stdc++.h>
#include "matrix.h"

using namespace std;
    
void executeMByBloques(Matrix A, Matrix B,Matrix C,int bsize){
    auto t1 = std::chrono::high_resolution_clock::now();
    A.multiplicacionBloques6(&B,&C,bsize);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    cout<<"tiempo: "<<duration/1000.0<<"\n";
}

int main() {
    int n=100;
    int bsize = 10;
    cout<<"-- Multiplicación de Matrices cuadraticas por bloques-- \n";
    for(int i=0 ; i<20 ; ++i){
        Matrix A(n),B(n),C(n);
        executeMByBloques(A,B,C,bsize);      
        A.freeMatrix();
        B.freeMatrix();
        C.freeMatrix();
        n += 100;
    }

    return 0;
}
