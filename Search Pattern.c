#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int SAD(int temp[2][2], int window[2][2],int size){
    // Compares our temp window from the frame to the desired window.
    // Takes in an array pointer for the window from the frame array and desired window array
    // as well as the window size in the format of length * width.
    // The 2d array will be read into a 1 dimensional array reading left to right top to bottom.
    // Returns an integer where 0 indicates we found the desired window.
    // Lower the integer the closer to the desired window we are.
    int sum = 0;
    int windowSum = 0;
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            sum += temp[i][j];
            windowSum += window[i][j];
        }
    }
    return sum-windowSum;
}

void ReadArr(int row, int col, int windowx, int windowy, int frame[4][4], int temp[2][2]){
    for(int i = row; i < row+windowx-1; i++){
        for(int j = col; j < col+windowy-1; j++){
            temp[i][j] = frame[i][j];
        }
    }
}



void SearchPattern(int framex, int framey, int windowx, int windowy, int frame[4][4], int window[2][2]) {
    int temp[windowx][windowy];
    int rows = framex; // Number of rows in the grid
    int cols = framey; // Number of columns in the grid
    int top = 0, bottom = rows, left = 0, right = cols;
    int direction = 0;
    int lowestSAD = 1000;
    int lowestSADIndexI;
    int lowestSADIndexJ;
    int tempSAD = 0;
    int i,j;




    while (top <= bottom && left <= right) {
        if (direction == 0) { // Move right
            i = top;
            for (j = left; j <= right; j++) {
                ReadArr(i, j, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowy);
                if(tempSAD<lowestSAD){
                    lowestSAD=tempSAD;
                    lowestSADIndexI = i;
                    lowestSADIndexJ = j;
                }
            }
            top++;
            direction = 1;
        } else if (direction == 1) { // Move down
            j=right;
            for (i = top; i <= bottom; i++) {
                ReadArr(i, j, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowy);
                if(tempSAD<lowestSAD){
                    lowestSAD=tempSAD;
                }
            }
            right--;
            direction = 2;
        } else if (direction == 2) { // Move left
            for (i = right; i >= left; i--) {
                ReadArr(i, j, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowy);
                if(tempSAD<lowestSAD){
                    lowestSAD=tempSAD;
                }
            }
            bottom--;
            direction = 3;
        } else if (direction == 3) { // Move up
            for (i = bottom; i >= top; i--) {
                ReadArr(i, j, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowy);
                if(tempSAD<lowestSAD){
                    lowestSAD=tempSAD;
                }
            }
            left++;
            direction = 0;
        }
    }
    printf("%d, %d", lowestSADIndexJ, lowestSADIndexI);
}

int main(int args){
    int asize0[4] = {4,4,2,2};
    int frame0[4][4] = {{0,0,1,2},
                        {0,0,3,4},
                        {0,0,0,0},
                        {0,0,0,0}};
    int window[2][2] = {{1,2},
                        {3,4}};

    SearchPattern(4,4,2,2, frame0, window);

    return 0;

}