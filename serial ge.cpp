/*
#include <iostream>
using namespace std;


int main(){


float input[4][5] = {
    {10,  2,  3,  4,  5},
    { 6, 17,  8,  9, 10},
    {11, 12, 23, 14, 15},
    {16, 17, 18, 29, 20}
};

for (int k=0; k<4; k++){
	for (int i=k+1; i<5; i++){
		float temp = input[i][k]/input[k][k];	
			for (int j=k+1; j<5; j++){
				input[i][j] = input[i][j] - (temp*input[k][j]);
				//cout<<input[i][j]<<endl ;
			
				}
	}
}

for (int r=0; r<4; r++){
	for (int c=0; c<5; c++){
		cout << "input[" << r << "][" << c << "] : " << input[r][c] << endl; 		
	}
}

return 0;
}
*/

/*
 * Description: Solve a hard coded linear system by gaussian elimination
 * Author: Silveira Neto
 * License: Public Domain
 */
 
#include <stdio.h>
#include <stdlib.h>
 
#define ROWS 4
#define COLS 5
 
/**
 * Linear System, Ax = B
 *
 * 10*x1 +  2*x2 +  3*x3 +  4*x4 = 5
 *  6*x1 + 17*x2 +  8*x3 +  9*x4 = 10
 * 11*x1 + 12*x2 + 23*x3 + 14*x4 = 15
 * 16*x1 + 17*x2 + 18*x3 + 29*x4 = 20
 */
float AB[ROWS][COLS] = {
    {10,  2,  3,  4,  5},
    { 6, 17,  8,  9, 10},
    {11, 12, 23, 14, 15},
    {16, 17, 18, 29, 20}
};
 
/* Answer x from Ax=B */
float X[ROWS] = {0,0,0,0};
 
int main(int argc, char** argv) {
    int row, col, i;
 
    /* gaussian elimination */
    for (col=0; col<COLS-1; col++) {
        for (row=0; row<ROWS; row++){
            float pivot =  AB[row][col]/AB[col][col];
            if(row!=col) {
                for(i=0; i<COLS; i++) {
                    AB[row][i] = AB[row][i] - pivot * AB[col][i];
                }
 
            }
        }
    }
for (int r=0; r<4; r++){
	for (int c=0; c<5; c++){
		printf("input[ %d ][%d ] : %f \n",r,c,AB[r][c]); 		
	}
}

return 0;
}
