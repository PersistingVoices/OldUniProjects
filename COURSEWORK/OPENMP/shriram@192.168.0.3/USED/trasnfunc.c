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

void loop2(void) {
	printf("-----------------LOOP2----------------\n");
	int i,j,k, Ars[4], Arf[4], Arnow[4], Tid = 0, Tid_max=0, Tnums=0,e=0;
	double start=0,finish=0, chunk_size=0.0,chunk_size_temp=0.0, finish_state=0.0, gap=0, max_gap=0;
	for(i=0;i<4;i++){Arf[i]=Ars[i]=Arnow[i]=0;}

	omp_set_num_threads(4);

	double rN2;

	rN2 = 1.0 / (double) (N*N);

#pragma omp parallel default(none) private(i,j,k,max_gap,Tid,Tid_max, Tnums, start, finish, gap, chunk_size, chunk_size_temp, finish_state) shared(a,b,c, Ars, Arf, Arnow, jmax, rN2)
	{


		chunk_size_temp=0.0,
			finish_state=0,
			chunk_size=0.0,
			start=0.0,
			finish=0.0,
			i=0,
			j=0,
			k=0;
		int e=0;

		Tid = omp_get_thread_num();
		//printf("Tid: %d\n", Tid);
		Tnums = omp_get_num_threads();
		//printf("Tnum: %d\n", Tnums);
		Ars[Tid] = N*Tid/Tnums;
		Arf[Tid] = N*(Tid+1)/Tnums -1;
		//printf("Asf: %d %d\n", Ars[Tid], Arf[Tid]);
		start = Ars[Tid];
		finish = Arf[Tid];

		e= start;
		chunk_size_temp = finish - start + 1;
		int work_done=0;

		while(!work_done){

			for (i=Ars[Tid]; i<Arf[Tid]; i++){

				chunk_size = ceil((chunk_size_temp)/Tnums);
				chunk_size_temp -= chunk_size;

				while(chunk_size!=0){
					for (j=0; j < jmax[e]; j++){
						for (k=0; k<j; k++){
							c[e] += (k+1) * log (b[e][j]) * rN2;
						}
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
				//printf("max_gap*Tid_max/Tnums=  (%lf * %d)/%d\n",max_gap, Tid_max, Tnums);
			}
		}
	}
	printf("-----------------LOOP2----------------\n");
}       

