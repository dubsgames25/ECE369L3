#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FRAME_WIDTH 32
#define FRAME_HEIGHT 32
#define BLOCK_SIZE 8
#define SEARCH_RANGE 7  // This will create a 15x15 search area

typedef unsigned char Pixel;
//FOR VISUAL
// Function to clear the frame
void clear_frame(char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
    for (int i = 0; i < FRAME_HEIGHT; i++) {
        for (int j = 0; j < FRAME_WIDTH; j++) {
            frame[i][j] = '.';
        }
    }
}
// Function to draw a block
void draw_block(char frame[FRAME_HEIGHT][FRAME_WIDTH], int x, int y, char ch) {
    for (int i = y; i < y + BLOCK_SIZE && i < FRAME_HEIGHT; i++) {
        for (int j = x; j < x + BLOCK_SIZE && j < FRAME_WIDTH; j++) {
            frame[i][j] = ch;
        }
    }
}

// Function to print the frame
void print_frame(char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
    for (int i = 0; i < FRAME_HEIGHT; i++) {
        for (int j = 0; j < FRAME_WIDTH; j++) {
            printf("%c", frame[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//IMPORTANT STUFF REGARDING LAB3
// Function to calculate Sum of Absolute Differences (SAD)
int calculate_sad(Pixel* current_block, Pixel* reference_block, int stride) {
    int sad = 0;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            sad += abs(current_block[i*stride + j] - reference_block[i*stride + j]);
        }
    }
    return sad;
}

// Main VBSME function with visualization using spiral search pattern
void vbsme_spiral_search(Pixel* current_frame, Pixel* reference_frame) {
    char visual_frame[FRAME_HEIGHT][FRAME_WIDTH];
    int start_x = 0;
    int start_y = 0;
    int best_sad = INT_MAX;
    int best_mx = 0, best_my = 0;


    //visual function calls
    clear_frame(visual_frame);
    draw_block(visual_frame, start_x, start_y, '#');
    print_frame(visual_frame);

    printf("Processing 8x8 block starting at center (%d,%d)\n", start_x, start_y);

    // Spiral search pattern
    int x = 0, y = 0;
    int dx[] = {1, 0, -1, 0};  // Right, Down, Left, Up
    int dy[] = {0, 1, 0, -1};
    int direction = 0;
    int steps = 1;
    int step_count = 0;
    int layer = 0;

    while (layer <= SEARCH_RANGE) {
        int search_x = start_x + x;
        int search_y = start_y + y;

        // Check if the current search position is valid
        if (search_x >= 0 && search_x + BLOCK_SIZE <= FRAME_WIDTH &&
            search_y >= 0 && search_y + BLOCK_SIZE <= FRAME_HEIGHT) {

            int sad = calculate_sad(&current_frame[start_y*FRAME_WIDTH + start_x],
                                    &reference_frame[search_y*FRAME_WIDTH + search_x],
                                    FRAME_WIDTH);

            if (sad < best_sad) {
                best_sad = sad;
                best_mx = x;
                best_my = y;
                printf("New best match found at (%d,%d) with SAD %d\n", search_x, search_y, sad);
            }

            // Visualize the current search position
            clear_frame(visual_frame);
            draw_block(visual_frame, start_x, start_y, '#');
            draw_block(visual_frame, search_x, search_y, '*');
            print_frame(visual_frame);
        }

        // Move to the next position in the spiral
        x += dx[direction];
        y += dy[direction];
        step_count++;

        if (step_count == steps) {
            direction = (direction + 1) % 4;
            step_count = 0;
            if (direction == 0 || direction == 2) {
                steps++;
                layer++;
            }
        }
    }

    printf("\nBest match found at (%d,%d) with SAD %d\n\n", start_x + best_mx, start_y + best_my, best_sad);

    // Visualize the best match
    clear_frame(visual_frame);
    draw_block(visual_frame, start_x, start_y, '#');
    draw_block(visual_frame, start_x + best_mx, start_y + best_my, '@');
    print_frame(visual_frame);
}

int main() {
    Pixel current_frame[FRAME_HEIGHT * FRAME_WIDTH];
    Pixel reference_frame[FRAME_HEIGHT * FRAME_WIDTH];

    // Initialize frames with some pattern (for demonstration)
    for (int i = 0; i < FRAME_HEIGHT * FRAME_WIDTH; i++) {
        current_frame[i] = i % 255;
        reference_frame[i] = (i + 10) % 255;  // Slight offset for demonstration
    }

    vbsme_spiral_search(current_frame, reference_frame);

    return 0;
}