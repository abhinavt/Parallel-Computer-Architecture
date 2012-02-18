#define _XOPEN_SOURCE 600
#include <pthread.h>
#include <iostream>
#include <fstream>
using namespace std; 
#define NUM_THREADS	2
#include <math.h>

// Barrier variable
pthread_barrier_t barr;

struct thread_data
{
   float **input;
   int nthread;
   int thread_id;
   int nrows;
};

/*
void *Proc(void *t){
	struct thread_data* temp;
	temp = (struct thread_data*) t;
//	cout << "thread id is : " << temp->thread_id << endl;
	int row = temp->nrows;
	int col = row + 1; 
	for (int a=0; a<row; a++){
            for (int b=0; b<col; b++){           
		cout << "input [" << a << "][" << b << "] : " <<  temp->input[a][b] << endl;
           }
	}
	pthread_exit(NULL);
}
*/

void *Proc (void *thread_arg ) {
	struct thread_data* my_data;
	my_data = (struct thread_data*) thread_arg;
	float **A = my_data->input;
	int no_threads = my_data->nthread;
	int no_rows = my_data->nrows;
	int thread_id = my_data->thread_id;

	for( int k = 0; k <no_rows - 1; k++)  {
cout<<"K is " <<k<<endl;
	int my_no_rows;
		//No. of rows handled by each thread:
		if ((no_rows - k - 1) % no_threads)
			my_no_rows =  ((no_rows - k - 1)/ no_threads) + 1 ;
		else
			my_no_rows =  (no_rows -k - 1)/ no_threads;

 cout<<"my_no_rows :"<<my_no_rows<<endl;
 cout<<"no_rows :"<<no_rows<<endl;

		// local variables:
		int start = 1+k+ thread_id*my_no_rows;
	 	if( start > no_rows ) 
			pthread_exit(0);
	cout<<"start is "<<start<<" for thread : "<<thread_id<<endl;	
		int end = start +k+ my_no_rows - 1;
		if( end >= no_rows)
			end = no_rows -1;

		float temp[my_no_rows];

	cout<<"end is "<<end<<endl;	


		// Computation Loop starts:
		for ( int cr = start; cr <= end; cr++ )  {
			temp[cr] = A[cr][k] / A[k][k];
			for ( int cc = 0; cc <= no_rows ; cc++ )  {
				if(cc< k+1)  { 
					A[cr][cc] = 0;
					cout<<"A["<<cr<<"]["<<cc<<"] :"<<A[cr][cc]<<endl;
				} else  {
					A[cr][cc] = A[cr][cc] - temp[cr] * A[k][cc];
					cout<<"A["<<cr<<"]["<<cc<<"] :"<<A[cr][cc]<<endl;
				}
			}
		}


		// Barrier Synchronization point
		int rc = pthread_barrier_wait(&barr);
		if(rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD)
		{
			printf("Could not wait on barrier\n");
			pthread_exit(NULL);
		}

		
} // end for k;

} // end for proc;

float** readinput(float** ptr,  struct thread_data* p, int* rows){

        ifstream is ("example.txt");
            int input;
            int data;
            int i=0;

        is >> input;
      	p->nrows = input;
        int row = input;
	rows = &input;
        int col = input+1;

        ptr = new float*[row];
       
        for(int i = 0; i < row; i++){
   
                ptr[i] = new float[col];    }

        for (int a=0; a<row; a++){
            for (int b=0; b<col; b++){
		is >> data;                
		ptr[a][b] = data;
//		cout << "ptr [" << a << "][" << b << "]" <<  ptr[a][b] << endl;
           }
	}
return(ptr);
}


/* Start of main */
int main(int argc, char *argv[]){
 

 struct thread_data in[NUM_THREADS];
 struct thread_data* p = &in[0];
 
 float **ptr;
 int* nrows;
  for ( int i =0; i<NUM_THREADS; i++)  {
	
 (p+i)->input = readinput(ptr, (p+i), nrows);
 (p+i)->nthread = NUM_THREADS;
// p->nrows = 4;
}
 pthread_t threads[NUM_THREADS];
 // Barrier initialization
 if(pthread_barrier_init(&barr, NULL, NUM_THREADS)) 
  {
        printf("Could not create a barrier\n");
        return -1;
  }


 for(int t=0;   t<NUM_THREADS;   t++){
     	in[t].thread_id = t;
	cout <<"In main: creating thread : " << t << endl;
	pthread_create(&threads[t], NULL, Proc, (void *) &in[t]);
 }

 for (int i=0; i< NUM_THREADS; i++){

	pthread_join(threads[i], NULL);
 }
/*
 for ( int i =0; i< *nrows; i ++)  {
	for( int j =0; j< *nrows + 1 ; j++)  {
		cout<<"matrix["<<i<<"]["<<j<<"] : "<< ptr[i][j]<< endl;
	}
 }
*/		 
cout << "ALL DONE" << endl;
}

