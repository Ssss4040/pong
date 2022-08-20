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

void paint_field(int *racket_middle_left, int *racket_middle_right, int *field);
int input();
void output_field(int *field);
int input_racket_left(int racket_move);
int input_racket_right(int racket_move);
void clear();

int main() {
    int field[SIZE_FIELD_WIDTH][SIZE_FIELD_LENGTH];
    int racket_middle_left = 12;
    int racket_middle_right = 12;
    int count = 0;
    while(count != 21) {
        paint_field(&racket_middle_left, &racket_middle_right, &field[0][0]);
    }
    return 0;
}

void paint_field(int *racket_middle_left, int *racket_middle_right, int *field) {
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if ((y == TOP_BIRDER) || (y == BOTTOM_BIRDER)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else if ((x == LEFT_BIRDER) || (x == RIGHT_BIRDER)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else if (x == (RIGHT_BIRDER/2) && ((y%2) == 0)) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else if ((x == START_RACKET_LEFT) && ((y ==*racket_middle_left) ||
              (y ==*racket_middle_left - 1) || (y ==*racket_middle_left + 1))) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else if ((x == START_RACKET_RIGHT) && ((y ==*racket_middle_right) ||
            (y ==*racket_middle_right -1) || (y ==*racket_middle_right + 1))) {
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else {
                field[y*SIZE_FIELD_WIDTH+x] = 0;
            }
        }
    }
    output_field(field);
    *racket_middle_left = input_racket_left(*racket_middle_left);
    *racket_middle_right = input_racket_right(*racket_middle_right);
}

int input_racket_left(int racket_move) {
    char input_move;
    scanf("%c", &input_move);
    switch (input_move) {
    case 'A': {if (racket_move != 2) racket_move--; } break;
    case 'a': {if (racket_move != 2) racket_move--; } break;
    case 'z': {if (racket_move != 22) racket_move++; } break;
    case 'Z': {if (racket_move != 22) racket_move++; } break;
    default: break;
    }
    return racket_move;
}

int input_racket_right(int racket_move) {
    char input_move;
    scanf("%c", &input_move);
    switch (input_move) {
    case 'K': {if (racket_move != 2) racket_move--; } break;
    case 'k': {if (racket_move != 2) racket_move--; } break;
    case 'm': {if (racket_move != 22) racket_move++; } break;
    case 'M': {if (racket_move != 22) racket_move++; } break;
    default: break;
    }
    return racket_move;
}

void output_field(int *field) {
    clear();
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


void clear() {
    for (int i = 0; i < 200; i++) {
        printf("\n");
    }
}