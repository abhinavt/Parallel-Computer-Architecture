// Final working code; consider '0' pivot element; with file IO
#define _XOPEN_SOURCE 600
#include <iostream>
#include <fstream>
#include<pthread.h>
#define NUM_THREAD 2

using namespace std;

int n;			// n = number of rows

struct thread_data{
	float** data;
	int pid;
};

pthread_barrier_t barr;

void* solve(void *thread_arg) {				// needed: pid, data, number of rows
	struct thread_data* my_data;
	my_data = (struct thread_data*) thread_arg;
	float** a;
	a = my_data->data;
	int id = my_data->pid;

	int i, j, k, max;
	float t;

	for (i = 0; i < n; ++i) {
	   if ((i+1)%NUM_THREAD == id){
		cout << "thread : " << id << "   working" << endl;
		if (a[i][i] == 0){
			max = i;
			for (j = i + 1; j < n; ++j)
				if (a[j][i] > a[max][i])
					max = j;
		
			for (j = 0; j < n + 1; ++j) {
				t = a[max][j];
				a[max][j] = a[i][j];
				a[i][j] = t;
			}
		}
		else {
			for (j = n; j >= i; --j)
				for (k = i + 1; k < n; ++k)				// i = PIVOT
					a[k][j] -= a[k][i]/a[i][i] * a[i][j];		
		}		
	  }
		pthread_barrier_wait(&barr);
//	  else 
				
	}
      
//	   else
//		continue;


/*		for (k = 0; k < n; ++k) {
			for (j = 0; j < n + 1; ++j)
			cout << a[k][j] << '\t';
			cout << '\n';
		//	cout << a[k][j]/a[k][k] << '\t';				// for normalization
		//	cout << '\n';								
		}						*/	
//return 0;
}



int main(int argc, char *argv[]) {

	
	struct thread_data in[NUM_THREAD];
	pthread_t threads[NUM_THREAD];
	pthread_barrier_init(&barr, NULL, NUM_THREAD);

	ifstream is ("example.txt");
        int input;
        int data;
        int i=0;
	float** ptr;

        is >> input;
      	n = input;
        int row = input;
        int col = input+1;

        ptr = new float*[row];
       
        for(int i = 0; i < row; i++){
   
                ptr[i] = new float[col];    
	}

        for (int a=0; a<row; a++){
            for (int b=0; b<col; b++){
		is >> data;                
		ptr[a][b] = data;
//		cout << "ptr [" << a << "][" << b << "]" <<  ptr[a][b] << endl;
           }
	}
	
	for (int i=0; i<NUM_THREAD; i++){
		in[i].data = ptr;
	}

	
	for(int t=0;   t<NUM_THREAD;   t++){
     		in[t].pid = t;
		cout <<"In main: creating thread : " << t << endl;
		pthread_create(&threads[t], NULL, solve, (void *) &in[t]);
 	}

//	solve(ptr, n);


	for(int i = 0; i < NUM_THREAD; ++i)
	    {
        	pthread_join(threads[i], NULL);
	    }

	for (int k = 0; k < n; ++k) {
		for (int j = 0; j < n + 1; ++j)
		cout << ptr[k][j] << '\t';
		cout << '\n';
	//	cout << a[k][j]/a[k][k] << '\t';				// for normalization
	//	cout << '\n';								
	}							


	delete [] ptr;
	return(0);
}


