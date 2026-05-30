#include <stdio.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 30

// Aspect ratio correction (important!)
#define Y_SCALE 2.5 // tweak between 1.8 – 2.2 depending on terminal

// 1. Initialize buffer
void initializeBuffer(char buffer[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            buffer[i][j] = ' ';
}

// 2. Draw proper circle border
void drawCircle(char buffer[HEIGHT][WIDTH], int cx, int cy, int r) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {

            double dx = (x - cx);
            double dy = (y - cy) * Y_SCALE;

            double dist = sqrt(dx*dx + dy*dy);

            // thin boundary
            if (fabs(dist - r) < 0.5) {
                buffer[y][x] = '*';
            }
        }
    }
}

// 3. Print buffer
void printBuffer(char buffer[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            printf("%c", buffer[i][j]);
        printf("\n");
    }
}

// 4. Main
int main() {
    char buffer[HEIGHT][WIDTH];

    initializeBuffer(buffer);

    drawCircle(buffer, WIDTH/2, HEIGHT/2, 10);

    printBuffer(buffer);

    return 0;
}