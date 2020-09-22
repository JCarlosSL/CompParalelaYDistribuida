#include<bits/stdc++.h>
#include "matrix.h"

using namespace std;
    
void executeMSinBloques(Matrix A,Matrix B,Matrix C){
    auto t1 = std::chrono::high_resolution_clock::now();
    A.multiplicacion(&B,&C);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    cout<<"tiempo: "<<duration/1000.0<<"\n";
}

int main() {
    int n=100;

    cout<<"--Test para Multiplicacion de Matrices  cuadradas sin bloques--\n";
    for(int i=0;i<10;++i){
        cout<< "Test "<<i+1<<" con n="<<n<<endl;
        Matrix A(n),B(n),C(n);
        executeMSinBloques(A,B,C);
        
        A.freeMatrix();
        B.freeMatrix();
        C.freeMatrix();
        n += 100;
    }

    return 0;
}
