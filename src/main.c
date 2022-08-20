#include <stdio.h>

#define SIZE_FIELD_WIDTH 80
#define SIZE_FIELD_LENGTH 25
#define MIDDLE_FIELD_LENGTH 12
#define START_RACKET_LEFT 1
#define START_RACKET_RIGHT 78
#define TOP_BIRDER 0
#define BOTTOM_BIRDER 24
#define LEFT_BIRDER 0
#define RIGHT_BIRDER 79

void paint_field(int *field);
void paint_raket(int racket_middle_left, int racket_middle_right, int *field);
void output_field(int *field);



int main() {
    int field[SIZE_FIELD_WIDTH][SIZE_FIELD_LENGTH];
    int racket_middle_left = 12;
    int racket_middle_right = 12;

    paint_field(&field[0][0]);
    paint_raket(racket_middle_left, racket_middle_right, &field[0][0]);
    output_field(&field[0][0]);
    
    return 0;
}

void paint_field(int *field) {
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if ((y == TOP_BIRDER) || (y == BOTTOM_BIRDER)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else {
                field[y*SIZE_FIELD_WIDTH+x] = 0;
            }
            if ((x == LEFT_BIRDER) || (x == RIGHT_BIRDER)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            }
            if (x == (RIGHT_BIRDER/2) && ((y%2) == 0)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            }
        }
    }
}

void paint_raket(int racket_middle_left, int racket_middle_right, int *field) {
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if ((x == START_RACKET_LEFT) && (y == racket_middle_left)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            }
            if ((x == START_RACKET_RIGHT) && (y == racket_middle_right)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            }
        }
    }
}

void output_field(int *field) {
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if (field[y*SIZE_FIELD_WIDTH+x] == 1) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        if (y != RIGHT_BIRDER) {
            printf("\n");
        }
    }
}
