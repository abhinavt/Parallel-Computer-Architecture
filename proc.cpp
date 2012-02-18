// Routine for the thread:

void *proc (void *thread_arg ) {
//	struct thread_data *my_data = thread_arg;
	float **A = thread_arg->input;
	int no_threads = thread_arg->nthread;
	int no_rows = thread_arg->nrows;
	int thread_id = thread_arg->thread_id;

	for( int k = 0; k <no_rows - 1; k++)  {
		  
		//No. of rows handled by each thread:
		int my_no_rows = ( (no_rows - k - 1)/ no_threads)	

		// local variables:
		int start = 1 + thread_id*my_no_rows;
	 	if( start > n ) 
			pthread_exit(0);
		
		int end = start + my_no_rows - 1;
		if( end > no_rows)
			end = n -1;
		
		// Computation Loop starts:
		for ( int cr = start; cr <= end; cr++ )  {
			A[cr][k] = A[cr][k] / A[k][k];
			for ( int cc = k+1; cc <= no_rows +1; cc++ )  {
				A[cr][cc] = A[cr][cc] - A[cr][k] * A[k][cc];
			}
		}

		// Barrier 
		barrier

} // end for k;

} // end for proc;
