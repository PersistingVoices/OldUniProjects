#include <stdio.h>
#include <math.h>


#define N 729
#define reps 100 
#include <omp.h> 

double a[N][N]={0}, b[N][N]={0}, c[N]={0};
int jmax[N];  


void init1(void);
void init2(void);
void loop1(void);
void loop2(void);
void valid1(void);
void valid2(void);


int main(int argc, char *argv[]) { 
  FILE *pFile2,*pFile1;
  FILE *pipe_gp1;

  double start1,start2,end1,end2,time1,time2;
  int r,i=0,rand(void);

  pFile1 = fopen ("file1.dat" , "w");
  pFile2 = fopen ("file2.dat" , "w");

  if (pFile1 == NULL || pFile2 ==NULL) perror ("Error opening file");

  for(i=0;i<10;i++)
  {
  init1(); 
  start1 = omp_get_wtime(); 
  for (r=0; r<reps; r++){ 
    loop1();
  } 
  end1  = omp_get_wtime();  

  valid1(); 
  time1 = (float)(end1-start1);
  printf("Total time for %d reps of loop 1 = %f\n",reps, time1); 
 
  
  init2(); 
  start2 = omp_get_wtime(); 
  for (r=0; r<reps; r++){ 
    loop2();
  } 
  end2  = omp_get_wtime(); 

  valid2(); 
  time2 =  (float)(end2-start2);
  // printf("Total time for %d reps of loop 2 = %f\n",reps, time2);
  // printf("This file is functional\n");

  // Write everything in the file, before plotting. 
  fprintf(pFile1,"%d\t%d\t%lf\n",rand()%100,i+1,time1);
  fprintf(pFile2,"%d\t%d\t%lf\n",rand()%100,i+1,time2); 
  }
  printf("\n\t\t\tWritten to 'file1.dat & file2.dat'\n\n"); 
  fclose(pFile1);
  fclose(pFile2);

  // Gnu-plot script
  pipe_gp1 = popen("gnuplot","w");
  fputs("set terminal wxt 0\n ", pipe_gp1);
  fputs("unset key\n ", pipe_gp1);
  fputs("set hidden3d\n ", pipe_gp1);
  fputs("set dgrid3d 50,50 qnorm 2\n ", pipe_gp1);
  fputs("set title 'Plot1'\n ", pipe_gp1);
  fputs("set xlabel'Random arrangement'\n ", pipe_gp1);
  fputs("set ylabel 'Number of Iterations'\n ", pipe_gp1);
  fputs("set zlabel 'Time taken'\n ", pipe_gp1);
  fputs("splot 'file1.dat' u 1:2:3 w lines \n ", pipe_gp1);
  fputs("set terminal png  size 1200,800 enhanced font 'Helvetica,15'\n ", pipe_gp1); 
  fputs("set output 'plot1.png'\n ", pipe_gp1);
  fputs("replot\n ", pipe_gp1);
  
  fputs("reset\n ", pipe_gp1);

  fputs("set terminal wxt 0\n ", pipe_gp1);
  fputs("unset key\n ", pipe_gp1);
  fputs("set hidden3d\n ", pipe_gp1);
  fputs("set dgrid3d 50,50 qnorm 2\n ", pipe_gp1);
  fputs("set title 'Plot2'\n ", pipe_gp1);
  fputs("set xlabel'Random arrangement'\n ", pipe_gp1);
  fputs("set ylabel 'Number of Iterations'\n ", pipe_gp1);
  fputs("set zlabel 'Time taken'\n ", pipe_gp1);
  fputs("splot 'file2.dat' u 1:2:3 w lines \n ", pipe_gp1);
  fputs("set terminal png  size 1200,800 enhanced font 'Helvetica,15'\n ", pipe_gp1); 
  fputs("set output 'plot2.png'\n ", pipe_gp1);
  fputs("replot\n ", pipe_gp1);
  
  pclose(pipe_gp1);
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





void loop1(void) {     //loop1
  int i,j; 
    
#pragma omp parallel for default(none) private(i,j) shared(a,b)
    for (i=0; i<N; i++){ 
      for (j=N-1; j>i; j--){
        a[i][j] += cos(b[i][j]);
      }  //for2 end
    }//for1 end
 }//void end

void loop2(void) {    //loop2

  int i,j,k; 
  double rN2;
  rN2 = 1.0 / (double) (N*N);
  
#pragma omp parallel for default(none) private(i,j,k) shared(c,b,jmax,rN2)
    for (i=0; i<N; i++){ 
      for (j=0; j < jmax[i]; j++){
        for(k=0;k<j;k++){
          c[i] += (k+1) * log (b[i][j]) * rN2;
         } //for3 end   
      } //for2 end
    }//for1 end
}//void end






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
 

