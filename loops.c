#include <stdio.h>
#include <math.h>


#define N 729
#define reps 1
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
  int i,j;

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


 // if (chunk_size!=0)
    // {
    // printf("Tid: %d, chunk_size= %lf\n",Tid,chunk_size);
    // }


void loop1(void) { 
  int i,j, Ars[4], Arf[4], Arnow[4], Tid = 0, Tid_max=0, Tnums=0,e=0;
  double start=0,finish=0, chunk_size=0.0,chunk_size_temp=0.0, finish_state=0.0, gap=0, max_gap=0;
  for(i=0;i<4;i++){Arf[i]=Ars[i]=Arnow[i]=0;} 

  omp_set_num_threads(4);


#pragma omp parallel default(none) private(max_gap ,i,j, Tid,Tid_max, Tnums, start, finish, gap, chunk_size, chunk_size_temp, finish_state) shared(a,b, Ars, Arf, Arnow)  
{   
  chunk_size_temp=0.0,finish_state=0,chunk_size=0.0,start=0.0,finish=0.0,i=0,j=0;
  
  Tid = omp_get_thread_num();
  Tnums = omp_get_num_threads();
  Ars[Tid] = N*Tid/Tnums;
  Arf[Tid] = N*(Tid+1)/Tnums -1;
  start = Ars[Tid];
  finish = Arf[Tid];

  chunk_size_temp = finish - start + 1;
  int e=0;
  e = start;
  for (i=start; i<=finish; i++){ 

    
    chunk_size = ceil((chunk_size_temp)/Tnums);
    if (chunk_size!=0)
    // printf("New chunk_size= %lf\n",chunk_size);
    chunk_size_temp -= chunk_size;
   
    while(chunk_size!=0){ 
        for (j=N-1; j>e; j--){
          a[e][j] += cos(b[e][j]);
        }
    e++;  
    chunk_size--; 
    }//while
  finish_state = 1;
  }//outermost for

if(finish_state==1){

#pragma omp critical
    {
      printf("Thread ID: %d\n",Tid);
      for ( i = 0; i < 4; ++i)
      { 
        max_gap = gap;
        gap = Arf[i] -Arnow[i];
        if(gap>max_gap)
        {
          max_gap= gap;
          Tid_max=i;
        }
      }
     chunk_size_temp = max_gap*Tid_max/Tnums;
     printf("max_gap*Tid/Tnums=  (%lf * %d)/%d\n",max_gap, Tid, Tnums);
    }      
  }//if

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
 

