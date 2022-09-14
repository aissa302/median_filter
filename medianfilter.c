#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFuncLibrary.h"

const int WINSIZE = 9; // This is a flattened 3x3 window size


//#define MAXCHAR 2048 // Maximum number of character per line in CSV file (ex: '225,225' = 7 characters)

int main(int argc, char const *argv[])
{
	int **filtered_matrix;
	int window[WINSIZE];

	//Load noisy matrix from CSV file
	int **noisy_matrix = read_csv("noisy.csv");

	// Make a copy with the same size of noisy matrix to store the cleaned matrix on.
	filtered_matrix = copy_matrix(RROWS, RCOLS, filtered_matrix, noisy_matrix);

	//Padding noisy matrix with zeors in the edges
	noisy_matrix = padding_zeros(ROWS, COLS, noisy_matrix);


	//Applying the median filter and store the cleaned matrix in filtred_matrix
	medianFilter(ROWS, COLS, filtered_matrix, window, noisy_matrix);

	
	//Load clean matrix from CSV file
	int **clean_matrix = read_csv("clean.csv");


	//Comparing cleaned noisy matrix with clean matrix
	compare_matrixs(RROWS, RCOLS, clean_matrix, filtered_matrix);

	//print cleaned matrix
	print_matrix(RROWS, RCOLS, filtered_matrix);
	
	int row;
	/*TO DO*/ 
	// Free all arrays allocated in the heap
	//DONE
	for(row = 0; row < ROWS; row++)
	{
		free(noisy_matrix[row]);
		
	}
	for(row = 0; row < RROWS; row++)
	{
		free(clean_matrix[row]);
		free(filtered_matrix[row]);
	}
	
	free(noisy_matrix);
	free(filtered_matrix);
	free(clean_matrix);

	return 0;
}
