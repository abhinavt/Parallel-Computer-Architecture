#include <pthread.h>
#include <iostream>
#include <fstream>
using namespace std; 
#define NUM_THREADS	4

struct thread_data
{
   int **input;
   int nthread;
   int thread_id;
   int nrows;
};


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

int** readinput(int** ptr,  struct thread_data* p){

        ifstream is ("example.txt");
            int input;
            int data;
            int i=0;

        is >> input;
      	p->nrows = input;
        int row = input;
        int col = input+1;

        ptr = new int*[row];
       
        for(int i = 0; i < row; i++){
   
                ptr[i] = new int[col];    }

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
 
 struct thread_data in;
 struct thread_data* p = &in;
 
 int **ptr;
 p->input = readinput(ptr, p);
 p->nthread = NUM_THREADS;
 p->nrows = 4;

 pthread_t threads[NUM_THREADS];

 for(int t=0;   t<NUM_THREADS;   t++){
     	in.thread_id = t;
	cout <<"In main: creating thread : " << t << endl;
	pthread_create(&threads[t], NULL, Proc, (void *) p);
 }

 for (int i=0; i< NUM_THREADS; i++){

	pthread_join(threads[i], NULL);
 }

cout << "ALL DONE" << endl;
}

