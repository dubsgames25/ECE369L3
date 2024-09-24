#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int SAD(int temp[4][4], int window[4][4],int size){
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
    return abs(sum-windowSum);
}

void ReadArr(int row, int col, int windowx, int windowy, int frame[16][16], int temp[4][4]){
    for(int i = 0; i < windowx; i++){
        for(int j = 0; j < windowy; j++){
            temp[i][j] = frame[row+i][col+j];
        }
    }
}



void SearchPattern(int framex, int framey, int windowx, int windowy, int frame[16][16], int window[4][4]) {

    int temp[8][16];
    int lowestSAD = INT_MAX; // Use INT_MAX to ensure any first comparison will succeed
    int lowestSADIndexI = 0;
    int lowestSADIndexJ = 0;
    int tempSAD = 0;

    // Spiral search boundaries
    int top = 0, bottom = framex - windowx;
    int left = 0, right = framey - windowy;
    // Spiral search direction: 0 = right, 1 = down, 2 = left, 3 = up
    int direction = 0;
    while (top <= bottom && left <= right) {
        if (direction == 0) {  // Move right
            for (int j = left; j <= right; j++) {
                ReadArr(top, j, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowx);
                if (tempSAD < lowestSAD) {
                    lowestSAD = tempSAD;
                    lowestSADIndexI = top;
                    lowestSADIndexJ = j;
                }
            }
            top++;  // Move the top boundary down
            direction = 1;
        } else if (direction == 1) {  // Move down
            for (int i = top; i <= bottom; i++) {
                ReadArr(i, right, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowx);
                if (tempSAD < lowestSAD) {
                    lowestSAD = tempSAD;
                    lowestSADIndexI = i;
                    lowestSADIndexJ = right;
                }
            }
            right--;  // Move the right boundary left
            direction = 2;
        } else if (direction == 2) {  // Move left
            for (int j = right; j >= left; j--) {
                ReadArr(bottom, j, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowx);
                if (tempSAD < lowestSAD) {
                    lowestSAD = tempSAD;
                    lowestSADIndexI = bottom;
                    lowestSADIndexJ = j;
                }
            }
            bottom--;  // Move the bottom boundary up
            direction = 3;
        } else if (direction == 3) {  // Move up
            for (int i = bottom; i >= top; i--) {
                ReadArr(i, left, windowx, windowy, frame, temp);
                tempSAD = SAD(temp, window, windowx);
                if (tempSAD < lowestSAD) {
                    lowestSAD = tempSAD;
                    lowestSADIndexI = i;
                    lowestSADIndexJ = left;
                }
            }
            left++;  // Move the left boundary right
            direction = 0;
        }
    }

    // Print the result with the lowest SAD
    printf("Lowest SAD found at position: %d, %d\n", lowestSADIndexI, lowestSADIndexJ);
}
    /*  int temp[windowx][windowy];
    int rows = framex; // Number of rows in the grid
    int cols = framey; // Number of columns in the grid
    int top = 0, bottom = rows, left = 0, right = cols;
    int direction = 0;
    int lowestSAD = 1000;
    int lowestSADIndexI = 0;
    int lowestSADIndexJ = 0;
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
    printf("%d, %d", lowestSADIndexI, lowestSADIndexJ);
}
*/
int main(){
    int asize0[4] = {4,4,2,2};
    int frame0[4][4] = {{0,0,1,2},
                        {0,0,3,4},
                        {0,0,0,0},
                        {0,0,0,0}};
    int window[2][2] = {{1,2},
                        {3,4}};


    int asize5[4] = {32, 32, 8, 16};

    int frame5[32][32] = {
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8},
            {1,1,1,1,1,10,1,1,1,1,1,1,1,1,1,1,2,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8}
    };

    int window5[8][16] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };


        int asize1[4] = {16, 16, 4, 4};  // framex, framey, windowx, windowy

        // 16x16 frame array (frame1)
        int frame1[16][16] = {
                {0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
                {2, 3, 32, 1, 2, 3, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30},
                {3, 4, 1, 2, 3, 4, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45},
                {0, 4, 2, 3, 4, 5, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60},
                {0, 5, 3, 4, 5, 6, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75},
                {0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 72, 78, 84, 90},
                {0, 4, 14, 21, 28, 35, 42, 49, 56, 63, 70, 77, 84, 91, 98, 105},
                {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120},
                {0, 9, 18, 27, 36, 45, 54, 63, 72, 81, 90, 99, 108, 117, 126, 135},
                {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150},
                {0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 121, 132, 143, 154, 165},
                {0, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 0, 1, 2, 3},
                {0, 13, 26, 39, 52, 65, 78, 91, 104, 114, 130, 143, 1, 2, 3, 4},
                {0, 14, 28, 42, 56, 70, 84, 98, 112, 126, 140, 154, 2, 3, 4, 5},
                {0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 3, 4, 5, 6}
        };

        // 4x4 window array (window1)
        int window1[4][4] = {
                {0, 1, 2, 3},
                {1, 2, 3, 4},
                {2, 3, 4, 5},
                {3, 4, 5, 6}
        };

    SearchPattern(16,16,4,4, frame1, window1);

    return 0;

}