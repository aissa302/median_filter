#ifndef MYFUNCLIBRARY_H
#define MYFUNCLIBRARY_H // just to avoid redefinition.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//const int ROWS = 7;
//const int COLS = 7;
//const int RROWS = 5;
//const int RCOLS = 5;
const int MAXCHAR = 2048;const int ROWS = 244; // The Real Rows size is 242 but to make padding we need to add 2 rows. on up and one down.      
const int COLS = 310; // same Real Cols size is 308, we adding 2 cols, one in the left and one in the right.
const int RROWS = 242; // Real ROWS size
const int RCOLS = 308; // Real COLS size

int** read_csv(char filename[])
{
	char line[MAXCHAR]; // To store the first line in the CSV file. Look at fgets() down.
	char *token; // a pixel (number) in the CSV matrix
	char *ptr; // for strtol function. just keep reading you will understand later

	int row = 0;
	int col = 0; 

	FILE *noisyMatrix;
	noisyMatrix = fopen(filename, "r");

	if (noisyMatrix == NULL){
		printf("Failed to open the file\n");
		system("pwd");
		exit(1);
	}

	// A 2D matrix to store the values imported from CSV file
	int **matrix = calloc(RROWS, sizeof(int*));


	//Fill the entire matrix with zeors
	for (row = 0; row < RROWS; row++){
		matrix[row] = calloc(RCOLS, sizeof(int)); // create a row with number of columns equals COLS.
		for(col = 0; col < RCOLS; col++){
			matrix[row][col] = 0;
		}
	}

	// We don't want to fill the extra rows and columns which we added (leave them as zeros)
	
	row = 0;
	col = 0;
	while(fgets(line, MAXCHAR, noisyMatrix)){ // Load the first line in CSV file into line.

		// splite the line into tokens using ','
		token = strtok(line, ",");

		while(token != NULL)
		{
			//Convert the token(number) from string to integer and store it in matrix array. just ignore (&ptr and 10) 
			matrix[row][col] = strtol(token, &ptr, 10);
			
			// Move to the next token in the line
			token = strtok(NULL, ",");
			col++;
		}
		row++;
		col = 0; // restart the column counter to fill the next row.
	}
	return matrix;
}

/* Function to sort an array using insertion sort. This function is a copy past from Geekstogeeks*/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void compare_matrixs(int rows, int cols, int **m1, int **m2)
{
	for (int row = 0; row < RROWS; row++){
		for(int col = 0; col < RCOLS; col++){
			if(m1[row][col] == m2[row][col]){
				continue;
			}
			else{
				printf("m1[%d][%d]=%d # m2[%d][%d]=%d Cell Not matched here!!!\n", row,col,m1[row][col], row,col,m2[row][col]);
				exit(1);
			}
		}
	}
	printf("They are matched\n");
}

void print_matrix(int rows, int cols, int **arr)
{
	for (int row = 0; row < rows; row++){
		for(int col = 0; col < cols; col++){
			printf("%d\t",arr[row][col]);
		}
		printf("\n");
	}
}

// Copy the element of the matrix src to dest (make a copy)
int** copy_matrix(int rows, int cols, int **dest, int **src)
{
	dest = calloc(rows, sizeof(int*));
	for (int row = 0; row < rows; row++){
		dest[row] = calloc(cols, sizeof(int));
		for(int col = 0; col < cols; col++){
			dest[row][col] = src[row][col];
		}
	}
	return dest;
}

int** padding_zeros(int rows, int cols, int **array)
{
	int **mat = calloc(rows, sizeof(int*));
	int row;
	int col;
	for (row = 0; row < rows; row++){
		mat[row] = calloc(cols, sizeof(int));
		for(col = 0; col < cols; col++){
			mat[row][col] = 0;
		}
	}
	for (row = 0; row < rows-2; row++){ // why rows -2?? array is just 242x308 in size while mat is 244x310
		for(col = 0; col < cols-2; col++){ // same here removing the two columns we padded 
			mat[row+1][col+1] = array[row][col]; // why row+1 and col+1?? mat is 244x310 after padding 
												 // and we wanna fill only size of array which is 242x308
												 // so we need to start from 1x1 to n-1xn-1 to leave the padding zeros not touched
		}
	}
	return mat;
}

void medianFilter(int rows, int cols, int **matrix, int window[], int **array){ // How about if window size is bigger!!!!

	for(int row = 1; row < rows-1; ++row)
    {
        for(int col = 1; col < cols-1; ++col)
        {
            //neighbor pixel values are stored in window including this pixel
            window[0] = array[row-1][col-1];
            window[1] = array[row-1][col];
            window[2] = array[row-1][col+1];
            window[3] = array[row][col-1];
            window[4] = array[row][col];
            window[5] = array[row][col+1];
            window[6] = array[row+1][col-1];
            window[7] = array[row+1][col];
            window[8] = array[row+1][col+1];
 
            //sort window array
            insertionSort(window,9);
            //put the result in the new array
            matrix[row-1][col-1]=window[4];   
        }
    }
}
#endif