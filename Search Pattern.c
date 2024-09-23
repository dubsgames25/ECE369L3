#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int SAD(int *temp, int *window,int size){
    // Compares our temp window from the frame to the desired window.
    // Takes in an array pointer for the window from the frame array and desired window array
    // as well as the window size in the format of length * width.
    // The 2d array will be read into a 1 dimensional array reading left to right top to bottom.
    // Returns an integer where 0 indicates we found the desired window.
    // Lower the integer the closer to the desired window we are.
    int sum = 0;
    int windowSum = 0;
    for (int i = 0; i < size; i++) {
            sum += temp[i];
            windowSum += window[i];
    }
    return sum-windowSum;
}

//TODO Implement read function to read in a window. Should return an array of the window
int[] ReadArr(int row, int col, int[] temp){

}



void SearchPattern(int framex, int framey, int windowx, int windowy) {
    int frame[framex][framey];
    int temp[windowx][windowy];
    int window[windowx][windowy];
    int rows = framex; // Number of rows in the grid
    int cols = framey; // Number of columns in the grid
    int top = 0, bottom = rows - windowx, left = 0, right = cols - windowy;
    int direction = 0;
    int lowestSAD = SAD(*temp, *window, windowx*windowy);
    int tempSAD = 0;
    int i,j;




    while (top <= bottom && left <= right) {
        if (direction == 0) { // Move right
            i = top;
            for (j = left; j <= right; j++) {
                temp = [0][0];
                tempSAD = SAD();
                if(tempSAD<lowestSAD){
                    lowestSAD=tempSAD;
                }
            }
            top++;
        } else if (direction == 1) { // Move down
            j=right;
            for (i = top; i <= bottom; i++) {
                // Process cell (i, right)
            }
            right--;
        } else if (direction == 2) { // Move left
            for (i = right; i >= left; i--) {
                // Process cell (bottom, i)
            }
            bottom--;
        } else if (direction == 3) { // Move up
            for (i = bottom; i >= top; i--) {
// Process cell (i, left)
            }
            left++;
        }

        direction = (direction + 1) % 4;
    }
}