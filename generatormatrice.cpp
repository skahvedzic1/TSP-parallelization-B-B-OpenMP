#include <iostream>
#include <limits.h>
int main ()
{
    int k=20; /*samo se ovaj broj mijenja za dimenzije matrice*/
    int mat[k][k];
    for(int i=0;i<k;i++) {
        for(int j=0;j<k;j++) {
            if(i>j) {
                int a=1+ (rand() % 100) ; /* promijeniti 100 ako hocemo drugaciji range*/
                mat[i][j]=a;
                mat[j][i]=a;
        }
            if(i==j) mat[i][j]=INT_MAX;
        }
    }
    std::cout<< "{";   
    for(int i=0; i<k;i++){
        std::cout<< "{";
            for(int j=0;j<k;j++) {
                std::cout << mat[i][j];
                if(j!=k-1) std::cout << ",";
                    if(j==k-1) std::cout << "}";
                        if(j==k-1 & i!=k-1) std::cout << ",\n";
            }
    }
    std::cout<< "}";
	return 0;
}