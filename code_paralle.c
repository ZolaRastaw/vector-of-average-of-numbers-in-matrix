#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Change the number for the size wanted
#define N 1000
#include <omp.h>

int main (void) {
  FILE *fn;
  int i, j;
  double x,y,matrix[N][N] = {{0}};

  //declaration of variables for the mean
  float total,min=0;
  float mean[N]= {0};
    
    //get the time
  double start, end;
  start= omp_get_wtime();

  //change the path for the file.txt containing the original matrix
  fn = fopen("/Users/alicecombernoux/Desktop/Hongrie/para/CMakelists.txt", "r");

  //Check if file exists
  if (fn == NULL ) {
    printf("The file does not work\n");
    exit(EXIT_FAILURE);
  }
  printf("\n");
    
#pragma omp parallel num_threads(3)
{
    //create the matrix
    #pragma omp parallel for private(j)
     for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            fscanf(fn,"%lf",&x);
            matrix[i][j] = x;
         }
     }
      printf("\n");
      fclose(fn);


    //one dimensional matrix, which contains the average of the numbers in a row
    #pragma omp parallel for private(j,total)
     for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            total=total + matrix[i][j];
         }
         mean[i]=total/N;
         total=0;
     }

     //find minimum value of the array
        min=mean[0];
      #pragma omp parallel for
      for (i=0;i<N;i++){
        if(min>mean[i])
        {
            min=mean[i];
        }
     }
}
    
 //Final result
 printf("The smallest average number in the vector is %lf\n",min);
 end=omp_get_wtime();
 printf("execution time is %f\n",end-start);



return(0);
}
