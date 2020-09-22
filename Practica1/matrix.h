#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
    public:
        double **mat;
        int n;
    public:
        Matrix(){};
        Matrix(int n){
            this->n = n;
            //asignar matriz
            this->mat = new double*[n];
            int i=0;
            for(i=0;i<this->n;++i){
                this->mat[i] = new double[n];
            }
        }
        void freeMatrix(){
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
         *  matB: matriz resultante de n*n
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

        void multiplicacionBloques6(Matrix *matA,Matrix *matB,int bsize){
            int i,j,k,ii,jj,kk;
            for(i = 0 ; i < this->n ; i +=bsize){
                for(j = 0 ; j < this->n ; j += bsize){
                    for(k = 0 ; k < this->n ; k += bsize){
                        for(ii = i ; ii < i + bsize ; ii++){
                            for(jj = j ; jj < j + bsize ; jj++){
                                for(kk = k ; kk < k + bsize ; kk++){
                                    matB->mat[ii][jj] += this->mat[ii][kk]
                                                    * matA->mat[kk][jj];
                                }
                            }
                        }
                    }
                }
            }
        }
};

#endif //matrix
