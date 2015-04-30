#include <stdio.h>
#include <math.h>

#define THREADS 24
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

OMP_NUM_THREADS= THREADS;

int main(int argc, char *argv[]) { 
	FILE *pFile2,*pFile1;
	FILE *pipe_gp1;

	double start1,start2,end1,end2,time1,time2;
	int r,i=0,rand(void);

	pFile1 = fopen ("Data/DYNAMIC-n--file1.dat" , "w");
	pFile2 = fopen ("Data/DYNAMIC-n--file2.dat" , "w");

	if (pFile1 == NULL || pFile2 ==NULL) perror ("Error opening file");

	for(i=0;i<100;i++)
	{
		init1(); 
		start1 = omp_get_wtime(); 
		for (r=0; r<reps; r++){ 
			loop1();
		} 
		end1  = omp_get_wtime();  

		valid1(); 
		time1 = (float)(end1-start1);
		//printf("Total time for %d reps of loop 1 = %f\n",reps, time1); 


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
		fprintf(pFile1,"%lf\t%d\t%lf\n",(i+1)*time1,i+1,time1);
		fprintf(pFile2,"%lf\t%d\t%lf\n",(i+1)*time2,i+1,time2); 
	}
	printf("\n\t\t\tWritten to 'DYNAMIC-n--file1.dat & DYNAMIC-n--file2.dat'\n\n"); 
	fclose(pFile1);
	fclose(pFile2);

	// Gnu-plot script
	pipe_gp1 = popen("gnuplot","w");
	fputs("set terminal wxt 0\n ", pipe_gp1);
	fputs("unset key\n ", pipe_gp1);
	fputs("set hidden3d\n ", pipe_gp1);
	fputs("set dgrid3d 50,50\n ", pipe_gp1);
	fputs("set title '3DPlot1'\n ", pipe_gp1);
	fputs("set xlabel'Random Axis Arrangement (for 3-d plot)'\n ", pipe_gp1);
	fputs("set ylabel 'Iteration Number'\n ", pipe_gp1);
	fputs("set zlabel 'Time taken for 100 iterations'\n ", pipe_gp1);
	fputs("splot 'Data/DYNAMIC-n--file1.dat' u 1:2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/DYNAMIC-n--3dplot.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);


	fputs("reset\n ", pipe_gp1);

	fputs("set terminal wxt 0\n ", pipe_gp1);
	fputs("unset key\n ", pipe_gp1);
	fputs("set title '2DPlot1'\n ", pipe_gp1);
	fputs("set xlabel 'Iteration Number'\n ", pipe_gp1);
	fputs("set ylabel 'Time taken for 100 iterations'\n ", pipe_gp1);
	fputs("plot 'Data/DYNAMIC-n--file1.dat' u 2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/DYNAMIC-n--2dplot.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);

	fputs("reset\n ", pipe_gp1);

	fputs("set terminal wxt 0\n ", pipe_gp1);
	fputs("unset key\n ", pipe_gp1);
	fputs("set hidden3d\n ", pipe_gp1);
	fputs("set dgrid3d 50,50\n ", pipe_gp1);
	fputs("set title 'Plot2'\n ", pipe_gp1);
	fputs("set xlabel'Random Axis Arrangement (for 3-d plot)'\n ", pipe_gp1);
	fputs("set ylabel 'Iteration Number'\n ", pipe_gp1);
	fputs("set zlabel 'Time taken for 100 iterations'\n ", pipe_gp1);
	fputs("splot 'Data/DYNAMIC-n--file2.dat' u 1:2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/DYNAMIC-n--3dplot.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);

	fputs("reset\n ", pipe_gp1);

	fputs("set terminal wxt 0\n ", pipe_gp1);
	fputs("unset key\n ", pipe_gp1);
	fputs("set title '2DPlot1'\n ", pipe_gp1);
	fputs("set xlabel 'Time taken for 100 iterations'\n ", pipe_gp1);
	fputs("set ylabel 'Iteration Number'\n ", pipe_gp1);
	fputs("plot 'Data/DYNAMIC-n--file2.dat' u 2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/DYNAMIC-n--2dplot.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);

	pclose(pipe_gp1);

	printf("\n\t\t\tPlots at 'DYNAMIC-n--plot1.png & DYNAMIC-n--plot2.png' for loop1 & loop2  (100I)\n\n"); 
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

void loop1(void) { 
	int i,j; 

#pragma omp parallel for default(none) private(i,j) shared(a,b) schedule( dynamic, 2)
	for (i=0; i<N; i++){ 
		for (j=N-1; j>i; j--){
			a[i][j] += cos(b[i][j]);
		} 
	}

} 

void loop2(void) {
	int i,j,k; 
	double rN2; 

	rN2 = 1.0 / (double) (N*N);  

#pragma omp parallel for default(none) private(i,j,k) shared(a,b,c,jmax,rN2) schedule( dynamic, 2)
	for (i=0; i<N; i++){ 
		for (j=0; j < jmax[i]; j++){
			for (k=0; k<j; k++){ 
				c[i] += (k+1) * log (b[i][j]) * rN2;
			} 
		}
	}

}

void valid1(void) { 
	int i,j; 
	double suma; 

	suma= 0.0; 
	for (i=0; i<N; i++){ 
		for (j=0; j<N; j++){ 
			suma += a[i][j];
		}
	}
	//printf("Loop 1 check: Sum of a is %lf\n", suma);

} 

void valid2(void) { 
	int i; 
	double sumc; 

	sumc= 0.0; 
	for (i=0; i<N; i++){ 
		sumc += c[i];
	}
	//printf("Loop 2 check: Sum of c is %f\n", sumc);
} 
