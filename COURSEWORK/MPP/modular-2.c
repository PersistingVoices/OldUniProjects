#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include "pgmio.h"

#define M 192
#define N 128

#define ProcX 3
#define ProcY 4

#define MP M/ProcX
#define NP N/ProcY
#define P (ProcX*ProcY)

#define MAXITER   1500
#define PRINTFREQ  200

#define PRECISION 0.1


void print_start(char* filename,float master_buf[][N]){

	printf("Processing %d x %d image on %d processes\n", M, N, P);
	printf("Number of iterations = %d\n", MAXITER);
	printf("\nReading <%s>\n", filename);
	pgmread(filename, master_buf, M, N);
	printf("\n");

}

void print_end(char* filename, float master_buf[][N]){

	printf("\nWriting <%s>\n", filename); 
	pgmwrite(filename, master_buf, M, N);
	printf("\n");

}

void broadcast(float master_buf[][N], float slave_buf[][NP],int co[]){

	int i, j, m_i,m_j;

	for (i=0;i<MP;i++){
		for(j=0;j<NP;j++){
			m_i = i + co[0] * M/ProcX;
			m_j = j + co[1] * N/ProcY;
			slave_buf[i][j] = master_buf[m_i][m_j];
		}
	}

}

void array_manip(float edge_array[][NP+2], float slave_buf[][NP], float old_array[][NP+2]){

	int i, j;

	for (i=0;i<MP+2;i++){
		for (j=0;j<NP+2;j++){
			edge_array[i][j]=0.0;
		}
	}

	for (i=1;i<MP+1;i++){
		for (j=1;j<NP+1;j++){
			edge_array[i][j]=slave_buf[i-1][j-1];
		}
	}

	for (i=0;i<MP+2;i++){
		for (j=0;j<NP+2;j++){
			old_array[i][j]=edge_array[i][j];
		}
	}
}

int  Halos_and_Calc( MPI_Comm Comm_2, float old_array[][NP+2], float new_array[][NP+2], float slave_buf[][NP], float edge_array[][NP+2], int u, int d, int l, int r, int rank, int size){

	MPI_Status stat;
	MPI_Request req;
	
	MPI_Datatype Chunk;
	MPI_Type_vector(MP,1,NP+2,MPI_FLOAT, &Chunk);
	MPI_Type_commit(&Chunk);
	
	int i,j, iter, count=0;
	float PixelValue = 0.0, gdeltaall=0.0, gdelta = 0.0, delta=0.0, avgPixelValue=0.0 ;
	
	for (iter = 1; iter<=MAXITER; iter++){
		if(iter%PRINTFREQ==0){
			if(rank==0){
				printf("Iteration %d", iter);
			}
		}


		MPI_Issend(&old_array[1][NP], 1, Chunk, u, 0, Comm_2, &req);
		MPI_Recv(&old_array[1][0], 1, Chunk, d, 0, Comm_2, &stat);
		MPI_Wait(&req, &stat);

		MPI_Issend(&old_array[1][1], 1, Chunk, d, 0, Comm_2, &req);
		MPI_Recv(&old_array[1][NP+1], 1,Chunk , u, 0, Comm_2, &stat);
		MPI_Wait(&req, &stat);

		MPI_Issend(&old_array[MP][1], NP,MPI_FLOAT,l, 0,Comm_2, &req);
		MPI_Recv(&old_array[0][1], NP,MPI_FLOAT, r, 0,Comm_2, &stat);
		MPI_Wait(&req, &stat);

		MPI_Issend(&old_array[1][1], NP,MPI_FLOAT,r, 0,Comm_2, &req);
		MPI_Recv(&old_array[MP+1][1], NP,MPI_FLOAT, l, 0,Comm_2, &stat);
		MPI_Wait(&req, &stat);

		for (i=1;i<MP+1;i++){
			for (j=1;j<NP+1;j++){
				new_array[i][j] = 0.25*(old_array[i-1][j] + old_array[i+1][j] + old_array[i][j-1] + old_array[i][j+1]
						- edge_array[i][j]);
			}
		}

		for(i=1;i<=MP;i++){
			for(j=1;j<=NP;j++){

				delta += ((new_array[i][j]-old_array[i][j])*(new_array[i][j]- old_array[i][j]));				
				PixelValue += new_array[i][j];
			}
		}


		PixelValue = PixelValue/(MP*NP);

		MPI_Reduce(&PixelValue, &avgPixelValue, 1, MPI_FLOAT, MPI_SUM, 0, Comm_2);

		if(rank==0){
			if(iter%PRINTFREQ==0){
				avgPixelValue = avgPixelValue/(size);
				printf("Iteration number:%d, and the average value of the pixels is: %f\n", iter, avgPixelValue);
			}
		}

		for (i=1;i<MP+1;i++){
			for (j=1;j<NP+1;j++){
				old_array[i][j]=new_array[i][j];
			}
		}  
 
		MPI_Allreduce(&delta, &gdeltaall, 1, MPI_FLOAT, MPI_SUM,Comm_2);

		gdelta = sqrt(gdeltaall/(M*N));
	
		count++;

		if(gdelta < PRECISION)
		{
			printf("iteration: %d\n\n", iter);
			break;
		}

		PixelValue = 0.0;
		gdeltaall  = 0.0;
		delta 	   = 0.0;
		gdelta     = 0.0;
		avgPixelValue = 0.0;
	}

	for (i=1;i<MP+1;i++){
		for (j=1;j<NP+1;j++){
			slave_buf[i-1][j-1] = old_array[i][j];
		}
	}

return count;

}


void bring_back_to_buffer(int co[], float slave_buf[][NP], float master_buf_2[][N]){

	int i,j, m_i, m_j;

	for(i=0;i<MP;i++){
		for(j=0;j<NP;j++){
			m_i = i + co[0] * M/ProcX;
			m_j = j + co[1] * N/ProcY;
			master_buf_2[m_i][m_j] = slave_buf[i][j];
		}
	}

}

int main (int argc, char **argv)
{	
	char fileread[] = "edge192x128.pgm"; char  filewrite[] = "image192x128.pgm";

	float old[MP+2][NP+2], new[MP+2][NP+2], edge[MP+2][NP+2];
	float masterbuf[M][N], slavebuf[MP][NP], masterbuf_2[M][N];

	int i, j, iter, master_i, master_j, location, rank, size, next, prev, count=0; 
	int step_count=0 ;
	float start = 0.0, end =0.0, timer =0.0;

	MPI_Init(&argc, &argv);

	int dims[2],periods[2],coords[2], down, up, left, right;

	dims[0] = ProcX;
	dims[1] = ProcY;
	periods[0]= periods[1]= 0;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm Comm2;
	MPI_Status status;
	MPI_Request request;
	
	if(size!=P){
		if(rank==0)printf("ERROR: size!=P\n");
		MPI_Finalize();
		exit(-1);
	}
/////////////////////////////////////////////cart create////////////////////////	

	start = MPI_Wtime();
	int carterror;

	carterror=MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &Comm2);
	if (carterror!= MPI_SUCCESS) printf("ERROR: Cart not created\n");

	MPI_Cart_coords(Comm2, rank, 2, coords);
	
	MPI_Cart_shift(Comm2,0,1,&right,&left);
	MPI_Cart_shift(Comm2,1,1,&down,&up);
	end = MPI_Wtime();
	timer = end-start;
	printf("Time taken to decompose: %f\n", timer);

/////////////////////////////////READ/////////////////////////////////////////

	start = MPI_Wtime();
	if(rank==0){
		print_start(fileread, masterbuf);
	}
	end  = MPI_Wtime();
	timer = start-end;
	printf("Reading time: %f\n", timer);

////////////////////////////////BROADCAST/////////////////////////////////////

	int berror;
	start = MPI_Wtime();
	berror= MPI_Bcast(masterbuf, M*N, MPI_FLOAT, 0, MPI_COMM_WORLD); // broadcasts the image's buffer size to all of the nodes available. 

	if(berror != MPI_SUCCESS)printf("NOT BROADCASTED\n");

	broadcast(masterbuf,slavebuf,coords);
	end  = MPI_Wtime();
	timer = start-end;
	printf("distrubuting time: %f\n", timer);

////////////////////////////////// manipulate arrays//////////////////////////

	start = MPI_Wtime();
	array_manip(edge, slavebuf, old);
	end  = MPI_Wtime();
	timer = start-end;
	printf("Arrays manipulating: %f\n", timer);

	start = MPI_Wtime();
	step_count = Halos_and_Calc(Comm2,old,new,slavebuf,edge, up, down, left, right, rank, size);
	end  = MPI_Wtime();
	timer = start-end;
	timer = timer/ step_count;
	printf("Average time per iteration to Swap Halos and Calcuate: %f\n", timer);

//////////////////////////////////Bring back to buffer////////////////////////////////////////////

	start = MPI_Wtime();
	bring_back_to_buffer(coords, slavebuf, masterbuf_2);
	MPI_Allreduce(masterbuf_2, masterbuf, M*N, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
	end  = MPI_Wtime();
	timer = start-end;
	printf("Bringing back to another buffer: %f\n", timer);

//////////////////////////////////////////////////////////////////////////////

	start = MPI_Wtime();
	if(rank==0){
		print_end(filewrite, masterbuf);
	}
	end  = MPI_Wtime();
	timer = start-end;
	printf("writing to image: %f\n", timer);

	MPI_Finalize();

}
