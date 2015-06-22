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

	pFile1 = fopen ("Data/file1.dat" , "w");
	pFile2 = fopen ("Data/file2.dat" , "w");

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
	printf("\n\t\t\tWritten to 'file1.dat & file2.dat'\n\n"); 
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
	fputs("set ylabel 'Number of Iterations'\n ", pipe_gp1);
	fputs("set zlabel 'Time taken'\n ", pipe_gp1);
	fputs("splot 'Data/file1.dat' u 1:2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/3dplot1.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);


	fputs("reset\n ", pipe_gp1);

	fputs("set terminal wxt 0\n ", pipe_gp1);
	fputs("unset key\n ", pipe_gp1);
	fputs("set title '2DPlot1'\n ", pipe_gp1);
	fputs("set xlabel 'Number of iterations'\n ", pipe_gp1);
	fputs("set ylabel 'Time taken'\n ", pipe_gp1);
	fputs("plot 'Data/file1.dat' u 2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/2dplot1.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);

	fputs("reset\n ", pipe_gp1);

	fputs("set terminal wxt 0\n ", pipe_gp1);
	fputs("unset key\n ", pipe_gp1);
	fputs("set hidden3d\n ", pipe_gp1);
	fputs("set dgrid3d 50,50\n ", pipe_gp1);
	fputs("set title 'Plot2'\n ", pipe_gp1);
	fputs("set xlabel'Random Axis Arrangement (for 3-d plot)'\n ", pipe_gp1);
	fputs("set ylabel 'Number of Iterations'\n ", pipe_gp1);
	fputs("set zlabel 'Time taken'\n ", pipe_gp1);
	fputs("splot 'Data/file2.dat' u 1:2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/3dplot2.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);

	fputs("reset\n ", pipe_gp1);

	fputs("set terminal wxt 0\n ", pipe_gp1);
	fputs("unset key\n ", pipe_gp1);
	fputs("set title '2DPlot1'\n ", pipe_gp1);
	fputs("set xlabel 'Number of iterations'\n ", pipe_gp1);
	fputs("set ylabel 'Time taken'\n ", pipe_gp1);
	fputs("plot 'Data/file2.dat' u 2:3 w lines \n ", pipe_gp1);
	fputs("set terminal png  size 1200,800\n ", pipe_gp1); 
	fputs("set output 'Plots/2dplot2.png'\n ", pipe_gp1);
	fputs("replot\n ", pipe_gp1);

	pclose(pipe_gp1);

	printf("\n\t\t\tPlots at 'plot1.png & plot2.png' for loop1 & loop2  (100I)\n\n"); 
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
	printf("-----------------LOOP1----------------\n");
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

		chunk_size_temp = Arf[Tid] - Ars[Tid] + 1;
		int e=0;
		e = Ars[Tid];

		int work_done = 0;

		while (!work_done) {
			for (i=Ars[Tid]; i<=Arf[Tid]; i++){
				chunk_size = ceil((chunk_size_temp)/Tnums);
				chunk_size_temp -= chunk_size;
				while(chunk_size!=0){
					for (j=N-1; j>e; j--){
						a[e][j] += cos(b[e][j]);
					}
					e++;
					Arnow[Tid]++;
					chunk_size--;
				}
			}
#pragma omp critical
			{
				//printf("Arnow[%d]: %d\n",Tid,Arnow[Tid]);

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

				if (max_gap > 1) {
					work_done = 1;
				} else {
					// change me
					Ars[Tid] = Arnow[Tid_max] + (max_gap / 2);
					Arnow[Tid] = Ars[Tid];
					Arf[Tid] = Arf[Tid_max];
					// change him/her
					Arf[Tid_max] = Ars[Tid];
					chunk_size_temp = max_gap*Tid_max/Tnums;
				}
			}
		}

	}// pragama
	printf("-----------------LOOP1----------------\n");

}

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


