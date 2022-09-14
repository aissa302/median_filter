#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFuncLibrary.h"

const int WINSIZE = 9; // This is a flat* 3x3 window size
//const int ROWS_ = 7;
//const int COLS_ = 7;
//const int RROWS_ = 5;
//const int RCOLS_ = 5;


int main(int argc, char const *argv[])
{
	int **filtered_matrix;
	int window[WINSIZE];
	int row;
	int col;

	/*
        {  0,  1,  2,  3, 4},
        {  1,  2,  3,  4, 5},
        {  2,  3,  4,  5, 6},
        {  3,  4,  5,  6, 7},
        {  4,  5,  6,  7, 8},
	*/

	int offset = 0;

	int **testMat = calloc(RROWS, sizeof(int*));
	for(row = 0; row < RROWS; row++){
		testMat[row] = calloc(RCOLS, sizeof(int));
		for(col = 0; col < RCOLS; col++){
			testMat[row][col] = col+offset;
		}
		offset++;
	}
        
	// Make a copy with the same size of noisy matrix to store the cleaned matrix on.
	filtered_matrix = copy_matrix(RROWS, RCOLS, filtered_matrix, testMat);

	print_matrix(RROWS, RCOLS, filtered_matrix);
	
	printf("[+] Padding noisy matrix with zeors in the edges...\n");
	testMat = padding_zeros(ROWS, COLS, testMat);

	printf("[+] Applying the median filter...\n");

	medianFilter(ROWS, COLS, filtered_matrix, window, testMat);
	//print_matrix(ROWS, COLS, filtered_matrix);


	//compare_matrixs(ROWS, COLS, clean_matrix, filtered_matrix);

	printf("[+] print cleaned matrix...\n");
	print_matrix(RROWS, RCOLS, filtered_matrix);
	

	for(row = 0; row < RROWS; row++)
	{
		free(filtered_matrix[row]);
	}
	
	free(filtered_matrix);

	return 0;
}