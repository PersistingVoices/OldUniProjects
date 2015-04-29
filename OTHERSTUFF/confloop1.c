#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
#define N 10
#define reps 100 
#include <omp.h> 
omp_lock_t lockt;

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

  else{

  // for(i=0;i<2;i++)
  // {
 
  init1(); 
  start1 = omp_get_wtime(); 
  // for (r=0; r<2; r++){ 
    loop1();
  // } 
  end1  = omp_get_wtime();  

  valid1(); 
  time1 = (float)(end1-start1);
  // printf("Total time for %d reps of loop 1 = %f\n",reps, time1); 
 
  
  // init2(); 
  // start2 = omp_get_wtime(); 
  // for (r=0; r<reps; r++){ 
  //   loop2();
  // } 
  // end2  = omp_get_wtime(); 

  // valid2(); 
  time2 =  (float)(end2-start2);
  // printf("Total time for %d reps of loop 2 = %f\n",reps, time2);
  // printf("This file is functional\n");

  // Write everything in the file, before plotting. 
  fprintf(pFile1,"%lf\t%d\t%lf\n",(i+1)*time1,i+1,time1);
  fprintf(pFile2,"%lf\t%d\t%lf\n",(i+1)*time2,i+1,time2); 
  }
  printf("\n\t\t\tWritten to 'file1.dat & file2.dat'\n\n"); 
  fclose(pFile1);
  fclose(pFile2);

  // Gnu-plot script
  // pipe_gp1 = popen("gnuplot","w");
  // fputs("set terminal wxt 0\n ", pipe_gp1);
  // fputs("unset key\n ", pipe_gp1);
  // fputs("set hidden3d\n ", pipe_gp1);
  // fputs("set dgrid3d 50,50 qnorm 2\n ", pipe_gp1);
  // fputs("set title 'Plot1'\n ", pipe_gp1);
  // fputs("set xlabel'Random arrangement'\n ", pipe_gp1);
  // fputs("set ylabel 'Number of Iterations'\n ", pipe_gp1);
  // fputs("set zlabel 'Time taken'\n ", pipe_gp1);
  // fputs("splot 'file1.dat' u 1:2:3 w lines \n ", pipe_gp1);
  // fputs("set terminal png  size 1200,800 enhanced font 'Helvetica,15'\n ", pipe_gp1); 
  // fputs("set output 'plot1.png'\n ", pipe_gp1);
  // fputs("replot\n ", pipe_gp1);
  
  // fputs("reset\n ", pipe_gp1);

  // fputs("set terminal wxt 0\n ", pipe_gp1);
  // fputs("unset key\n ", pipe_gp1);
  // fputs("set hidden3d\n ", pipe_gp1);
  // fputs("set dgrid3d 50,50 qnorm 2\n ", pipe_gp1);
  // fputs("set title 'Plot2'\n ", pipe_gp1);
  // fputs("set xlabel'Random arrangement'\n ", pipe_gp1);
  // fputs("set ylabel 'Number of Iterations'\n ", pipe_gp1);
  // fputs("set zlabel 'Time taken'\n ", pipe_gp1);
  // fputs("splot 'file2.dat' u 1:2:3 w lines \n ", pipe_gp1);
  // fputs("set terminal png  size 1200,800 enhanced font 'Helvetica,15'\n ", pipe_gp1); 
  // fputs("set output 'plot2.png'\n ", pipe_gp1);
  // fputs("replot\n ", pipe_gp1);
  
  // pclose(pipe_gp1);
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

// void loop11( int* start[], int* finish[])
// {

// }


void loop1(void) 
{ 
  float range=0.0,start=0.0,finish=0.0;  //loop1  
  int i=0,j=0,tid=0,max=0, numt =0,load=0,loadL=0,loadN=0,s=0,m=0, temp=0, temp2=0;
  int loadH[32]={0};
  int psum=0; // processor speed
  int k =0; //chunk size control variable
  int remH=0,remL=0, state=0;
  omp_lock_t  lck;
  omp_init_lock(&lck);
  int Ars[4],Arf[4], Arrem[4];
  #ifdef _OPENMP
     (void) omp_set_dynamic(0);
     if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
     (void) omp_set_num_threads(4);
  #endif

  // loadH = (int*)malloc(omp_get_num_threads());

  #pragma omp parallel default(none) private(m,max,temp,state,Ars,Arf,Arrem,i,j,k,tid,finish,start,numt,range,s,temp2) shared(a,b) 
  { 

    temp2=0,temp=0,state=0,range=0.0,start=0.0,finish=0.0,numt=0,tid=0,s=0;  //initialise to 0
    for(i=0;i<4;i++){Arf[i]=Ars[i]=Arrem[i]=0;} //initialise to 0

    tid = omp_get_thread_num();
    numt = omp_get_num_threads();
    
    start = ceil(100*tid/numt);
    finish = ceil(100*(tid+1)/numt);
    Ars[omp_get_thread_num()] = start;
    Arf[omp_get_thread_num()] = finish;
    
    ///////////////////////////////////////////////////////////////////////////
    /////////////// make array to store start, finish//////////////////////////
    /////////////// make array to monitor range////////////////////////////////
    /////////////// make execution into function///////////////////////////////
    /////////////// skrew the load factor,calculate how much is left instead///
    /////////////// local array, then looks at the one with most iterations left, 
    /////////////// and allocates itself a new start and finish element, 
    /////////////// and updates that other thread's element, (not really)? 
    ///////////////////////////////////////////////////////////////////////////
    
    for(i=start;i<finish;i++)
    { 
      range = ceil(((finish-start)-temp)/omp_get_num_threads());  
      temp = temp + range;
      while(range!=0) //perform local stepped loops
      { 
        s++;
        Arrem[omp_get_thread_num()]=finish-s;
       
        for ( j = N-1 ; j > i ; j-- )
          {
            a[i][j] += cos(b[i][j]);      
          }//for2 end
        // printf("S: %d, f: %d, M: %d \n",Ars[omp_get_thread_num()],Arf[omp_get_thread_num()],Arrem[omp_get_thread_num()]  );
        range--;
      }// while end
     state =1;
    }//for end
    if (state==1)
    {       
    #pragma omp critical
      { 
      
      temp2=0;
        for(m=0;m<4;m++)
          {
            temp2= Arrem[m]-Arf[m];
            if(temp2>max){
              max=temp2;
            }
          }
      printf("\n");
      printf("Current thread checking :%d\n",omp_get_thread_num() );
      printf("Max remaining: %d\n",max);
      sleep(1);
      }     
    }
    printf("\n\n");
   }//pragma1 end
  }//void end

 
void loop2(void) {    //loop2
  int i,j,k, P=0; 
  double rN2;
  rN2 = 1.0 / (double) (N*N);

// #pragma omp parallel for default(none) private(i,j,k) shared(c,b,jmax,rN2) schedule (dynamic)
//     for (i=0; i<N; i++){ 
//       for (j=0; j < jmax[i]; j++){
//         for(k=0;k<j;k++){
//           c[i] += (k+1) * log (b[i][j]) * rN2;
//          } //for3 end   
//       } //for2 end
//     }//for1 end
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
  // printf("Loop 1 check: Sum of a is %lf\n", suma);

} 


void valid2(void) { 
  int i; 
  double sumc; 
  
  sumc= 0.0; 
  for (i=0; i<N; i++){ 
    sumc += c[i];
  }
  // printf("Loop 2 check: Sum of c is %f\n", sumc);
} 
 

// switch(tid){
//         case 0: sum0++;
//         break;
//         case 1: sum1++;
//         break;
//         case 2: sum2++;
//         break;
//         case 3: sum3++;
//         default: 
//         break;
//       }
//     printf("\nthread 0 (chunk size): %d\n",sum0);
//     printf("\nthread 1 (chunk size): %d\n",sum1);
//     printf("\nthread 2 (chunk size): %d\n",sum2);
//     printf("\nthread 3 (chunk size): %d\n",sum3);
//     printf("LOOP2 START\n");
//     