#include <bits/stdc++.h>

class Matrix{
    public:
        int **mat;
        int n;
    public:
        Matrix(){};
        Matrix(int n){
            std::cout<<"asignando memoria a la matriz \n";
            this->n = n;
            //asignar matriz
            this->mat = new int*[n];
            int i=0;
            for(i=0;i<this->n;++i){
                this->mat[i] = new int[n];
            }
        }
        void clearMatrix(){
            std::cout<<"liberando memoria asignada a la matriz \n";
            int i;
            for(i=0;i<this->n;i++){
                delete [] this->mat[i];
            }
            delete [] this->mat;
        }
        void printMatrix(){
            //mostrar matriz
            int i,j;
            for(i = 0 ; i < this->n ; i++){
                for(j = 0 ; j < this->n ; j++){
                    std::cout<<this->mat[i][j]<<"\t";
                }
                std::cout<<std::endl;
            }
        }
        void add(int i,int j,int value){
            this->mat[i][j] = value;
        }
        // multiplicacion normal
        void multiplicacion(Matrix *matA,Matrix *matB){                 
            int i,j,k;
            for(i = 0 ; i < this->n ; i++){
                for(j = 0 ; j < this->n ; j++){
                    for(k = 0 ; k < this->n ; k++){
                        matB->mat[i][j] += this->mat[i][k] * matA->mat[k][j];
                    }
                }
            }
        }
        /* multiplicacion por bloques
         *  parametros
         *  matA: matriz de n*n
         *  matB: matriz de n*n
         *  bsize: tamaño del bloque.
         */
        void multiplicacionBloques(Matrix *matA,Matrix *matB,int bsize){
            int kk,jj,i,j,k;
            for(kk = 0 ; kk < this->n ; kk += bsize){                            
                for(jj = 0; jj<this->n ;jj += bsize){
                    for(i = 0 ; i < this->n ; i++){
                        for(j = jj ;j < jj+bsize ; j++){
                            for(k = kk ; k < kk+bsize ; k++){
                                matB->mat[i][j] += this->mat[i][k]
                                                * matA->mat[k][j];
                            }
                        }
                    }
                }
            }

        }
};

int main(){

    int n=1000;
    Matrix A(n),B(n),C(n);
    /*int i,j;
    for(i=0;i<n;++i){
        for(j=0;j<n;++j){
            A.add(i,j,i*j);
            B.add(i,j,i+j);
        }
    }*/
    //A.printMatrix();
    //A.clearMatrix();
    A.multiplicacionBloques(&B,&C,100);
    //B.printMatrix();
    //C.printMatrix();
    A.clearMatrix();
    B.clearMatrix();
    C.clearMatrix();
    return 0;
}


