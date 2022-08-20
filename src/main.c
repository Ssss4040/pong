#include <stdio.h>

#define SIZE_FIELD_WIDTH 80
#define SIZE_FIELD_LENGTH 25
#define MIDDLE_FIELD_LENGTH 12
#define START_RACKET_LEFT 2
#define START_RACKET_RIGHT 78
#define TOP_BIRDER 0
#define BOTTOM_BIRDER 24
#define LEFT_BIRDER 0
#define RIGHT_BIRDER 79


void paint_field(int *field);
void output_field(int *field);


int main() {
    int field[SIZE_FIELD_WIDTH][SIZE_FIELD_LENGTH];
    paint_field(&field[0][0]);
    output_field(&field[0][0]);
    return 0;
}

void paint_field(int *field) {
    for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
        for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
            if (x == TOP_BIRDER || x == BOTTOM_BIRDER) {
                field[x*SIZE_FIELD_WIDTH+y] = 1;
            }
        }
    }
}

void output_field(int *field) {
    for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
        for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
            if (field[x*SIZE_FIELD_WIDTH+y] == 1) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        if (x != BOTTOM_BIRDER) {
            printf("\n");
        }
    }
}
