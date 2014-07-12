
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define DIM 500

void fill_random_values(int a[DIM][DIM], int m)
{
    int i, j;
    srand((unsigned int)time(NULL));
    for(i=0; i < m; i++)
	for(j=0; j< m; j++)
	    a[i][j] = rand();
}

void view_matrice(int a[DIM][DIM], int m)
{
    int i,j;
    for(i=0; i < m; i++){
	for(j=0; j< m; j++){
	    printf(" %08x", a[i][j]);
	}
	printf("\n");
    }
    printf("\n");

}

void mmultiply(int a[DIM][DIM], 
    int b[DIM][DIM],int c[DIM][DIM],int m,int n,int p)
{
    int i,j,k,sum=0;

    #pragma omp parallel for shared(c, m, p) private(i,j,k) 
    for (i=0;i<m;i++)
    {
	for (j=0;j<p;j++)
	{
	    for (k=0;k<n;k++)
		sum=sum+(a[i][k]*b[k][j]);
	    c[i][j]=sum;
	    sum=0;
	}
    }
    return;
}


void mmultiply(int a[DIM][DIM], 
    int b[DIM][DIM],int c[DIM][DIM],int m,int n,int p)
{
    int i,j,k,sum=0;

    for (i=0;i<m;i++)
    {
	for (j=0;j<p;j++)
	{
	    for (k=0;k<n;k++)
		sum=sum+(a[i][k]*b[k][j]);
	    c[i][j]=sum;
	    sum=0;
	}
    }
    return;
}

int main(int argc, char *argv[])
{
    int a[DIM][DIM];
    int b[DIM][DIM];
    int c[DIM][DIM];
    clock_t clock1, clock2;
    printf("Program will multiply %d x %d matrices\n", DIM, DIM);    
    printf("Method : Standart\n");
    fill_random_values(a, DIM);
    //view_matrice(a, DIM);
    fill_random_values(b, DIM);
    //view_matrice(b, DIM);
    printf("Random Matrices are ready\n");
    
    clock1 = clock();
    mmultiply(a,b,c,DIM,DIM,DIM);
    clock2 = clock();
    printf("Multiplication completed, duration = %d\n", clock2 - clock1);
    
    //view_matrice(c, DIM);
    return 0;
}


