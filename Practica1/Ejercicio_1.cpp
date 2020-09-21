#include <bits/stdc++.h>
using namespace std;

void asignarmemoria(double **&A,double *&x,double *&y,int MAX){
    A=new double*[MAX];
    x=new double[MAX];
    y=new double[MAX];
    for(int i=0;i<MAX;++i){
        A[i]=new double[MAX];
    }
}
void freememoria(double **&A,int MAX){
    for(int i=0;i<MAX;++i){
        delete[] A[i]; 
    }
    delete [] A;
}

void function1(int MAX){
    double **A,*x,*y;
    asignarmemoria(A,x,y,MAX);
    int i,j;
    auto t1 = chrono::high_resolution_clock::now();
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            y[i] += A[i][j]*x[j];
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    cout<<"function1: "<< duration/1000.0<<"\n";
    freememoria(A,MAX);
    free(x);
    free(y);
}

void function2(int MAX){
    double **A,*x,*y;
    asignarmemoria(A,x,y,MAX);
    int i,j;
    auto t1 = std::chrono::high_resolution_clock::now();
    for(j=0;j<MAX;j++){
        for(i=0;i<MAX;i++){
            y[i] += A[i][j]*x[j];
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    cout<<"function2: "<< duration/1000.0<<"\n";
    freememoria(A,MAX);
    free(x);
    free(y);
}


int main(int argc, char const** argv){

    int MAX = 10;
    cout<<"Test Ejercicio 1 \n";
    for(int i=0;i<5;++i){
        cout<<"test "<<i+1<<" con MAX="<<MAX<<":"<<endl;
        function1(MAX);
        function2(MAX);
        MAX *=10;
    }
    return 0;
}
