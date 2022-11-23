#ifndef BLOCKI
#define BLOCKI 64
#endif
#ifndef BLOCKJ
#define BLOCKJ 64
#endif
#ifndef BLOCKK
#define BLOCKK 256
#endif

#ifndef TYPE
#define TYPE double
#endif
#include <iostream>
#include "../src/mipp.h"

extern "C" {
double k_1x1x1(TYPE *vA, TYPE *vB, TYPE *vC);
}
TYPE k_1x1x1(TYPE *vA, TYPE *vB, TYPE *vC) { 
    const int nv=mipp::N<TYPE>();                  
    TYPE *B=&vB[0];                
    TYPE *C=&vC[0];                
    TYPE *A=&vA[0];                               
    for (int i=0;i<BLOCKI;i+=1) {                
       for (int j=0;j<BLOCKJ;j+=1*nv) {           
          mipp::Reg<TYPE> c00;
          c00.load(&C[(i+0)*BLOCKJ + j + (0)*nv]);
          for (int k=0;k<BLOCKK;k+=1) {            
             mipp::Reg<TYPE> a00;
             a00 = mipp::set1<TYPE>(A[(i+0)*BLOCKK+k+0]);
             mipp::Reg<TYPE> b00;
             b00.load(&B[(k+0)*BLOCKJ + j + (0)*nv]);
             c00 =mipp::fmadd(a00, b00,c00);
          }
          c00.store(&C[(i+0)*BLOCKJ + j + (0)*nv]);
       }                                           
    }
    return C[0];
}

int main(int argc, char** argv)
{
  mipp::vector<TYPE> A(BLOCKI*BLOCKK);
  mipp::vector<TYPE> B(BLOCKK*BLOCKJ);
  mipp::vector<TYPE> C(BLOCKI*BLOCKJ);
  TYPE s=0;
  for (int i=0;i<100;i++) 
    s+=k_1x1x1(&A[0],&B[0],&C[0]);
  std::cout << s;
  return 0;
}

