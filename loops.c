#include <stdio.h>
#include <math.h>


#define N 729
#define reps 100 
#include <omp.h> 

double a[N][N], b[N][N], c[N];
int jmax[N];  


void init1(void);
void init2(void);
void loop1(void);
void loop2(void);
void valid1(void);
void valid2(void);


int main(int argc, char *argv[]) { 
  FILE *pFile;

  double start1,start2,end1,end2,time1,time2;
  int r;

  init1(); 

  start1 = omp_get_wtime(); 

  for (r=0; r<reps; r++){ 
    loop1();
  } 

  end1  = omp_get_wtime();  

  valid1(); 
  time1 = (float)(end1-start1);
  printf("Total time for %d reps of loop 1 = %f\n",reps, time1); 
 
  pFile = fopen ("myfile.txt" , "w");
  if (pFile == NULL) perror ("Error opening file");
  
  init2(); 

  start2 = omp_get_wtime(); 

  for (r=0; r<reps; r++){ 
    loop2();
  } 

  end2  = omp_get_wtime(); 

  valid2(); 

  time2 = (float)(end2-start2);
  printf("Total time for %d reps of loop 2 = %f\n",reps, time2); 
  printf("This file is functional\n"); 
  fprintf(pFile,"%lf\t%lf\n",time1, time2);  
  fclose(pFile);
} 

void init1(void){
  int i,j, Ars[4], Arf[4], Ardone[4];

  for (i=0; i<N; i++){ 
    for (j=0; j<N; j++){ 
      a[i][j] = 0.0; 
      b[i][j] = 3.142*(i+j); 
    }
  }

}

void init2(void){ 
  int i,j, expr; 

  for (i=0; i<N; i++){ 
    expr =  i%( 3*(i/30) + 1); 
    if ( expr == 0) { 
      jmax[i] = N;
    }
    else {
      jmax[i] = 1; 
    }
    c[i] = 0.0;
  }

  for (i=0; i<N; i++){ 
    for (j=0; j<N; j++){ 
      b[i][j] = (double) (i*j+1) / (double) (N*N); 
    }
  }
 
} 

void loop1(void) { 
  int i,j, Ars[4], Arf[4], Ardone[4], Tid = 0, Tnums=0;
  double start=0,finish=0, chunk_range=0.0,chunk_range_temp=0.0, finish_state=0.0, place=0 ;
  for(i=0;i<4;i++){Arf[i]=Ars[i]=Ardone[i]=0;} 

  omp_set_num_threads(2);


#pragma omp parallel default(none) private(i,j, Tid, Tnums, start, finish, place, chunk_range, chunk_range_temp, finish_state) shared(a,b, Ars, Arf, Ardone)  
{   
  chunk_range_temp=0,finish_state=0,chunk_range=0.0,start=0.0,finish=0.0;

  Tid = omp_get_thread_num();
  Tnums = omp_get_num_threads();
  Ars[Tid] = N*Tid/Tnums;
  Arf[Tid] = N*(Tid+1)/Tnums - 1;
  start = Ars[Tid];
  finish = Arf[Tid];
  // printf("Ars: %d, Arf:%d \n",Ars[Tid], Arf[Tid]);

        for (i=start; i<finish; i++){ 
          
          chunk_range = ceil(((finish-start)-chunk_range_temp)/omp_get_num_threads());

          chunk_range_temp = chunk_range_temp + chunk_range; 
          
          while(chunk_range!=0){
              for (j=N-1; j>i; j--){
                a[i][j] += cos(b[i][j]);
              }
          chunk_range--; 
          }//while 
        finish_state = 1;
        }//outermost for

}// pragama
}

void loop2(void) {
  int i,j,k; 
  double rN2; 

// rN2 = 1.0 / (double) (N*N);  


//   for (i=0; i<N; i++){ 
//     for (j=0; j < jmax[i]; j++){
//       for (k=0; k<j; k++){ 
// 	c[i] += (k+1) * log (b[i][j]) * rN2;
//       } 
//     }
  // }


}//end void

void valid1(void) { 
  int i,j; 
  double suma; 
  
  suma= 0.0; 
  for (i=0; i<N; i++){ 
    for (j=0; j<N; j++){ 
      suma += a[i][j];
    }
  }
  printf("Loop 1 check: Sum of a is %lf\n", suma);

} 


void valid2(void) { 
  int i; 
  double sumc; 
  
  sumc= 0.0; 
  for (i=0; i<N; i++){ 
    sumc += c[i];
  }
  printf("Loop 2 check: Sum of c is %f\n", sumc);
} 
 

