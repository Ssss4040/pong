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

void paint_field(int *racket_middle_left, int *racket_middle_right, int *ball_width, int *ball_length, int *field);
int input();
void output_field(int *field);
int input_racket_left(int racket_move);
int input_racket_right(int racket_move);
void clear();
void move_ball(int *ball_width, int *ball_length, int *movement_width, int *movement_length, int *racket_middle_left, int *racket_middle_right);
void check_hit_ball(int *ball_width, int *movement_width, int *racket_middle_left, int *racket_middle_right);

int main() {
    int field[SIZE_FIELD_WIDTH][SIZE_FIELD_LENGTH];
    int racket_middle_left = 12;
    int racket_middle_right = 12;
    int ball_width = 2, ball_length = 12;
    int movement_width = 1, movement_length = 1;
    int count = 0;
    while(count != 21) {
        paint_field(&racket_middle_left, &racket_middle_right, &ball_width, &ball_length, &field[0][0]);
        printf("racket left: %d, racket right: %d, ball width: %d, ball length: %d\n", racket_middle_left, racket_middle_right, ball_width, ball_length);
        move_ball(&ball_width, &ball_length, &movement_width, &movement_length, &racket_middle_left, &racket_middle_right);
    }
    return 0;
}

void paint_field(int *racket_middle_left, int *racket_middle_right, int *ball_width, int *ball_length, int *field) {
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
            } else if ((y == *ball_length) && (x == *ball_width)) {
                field[y*SIZE_FIELD_WIDTH+x] = 2;
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

void move_ball(int *ball_width, int *ball_length, int *movement_width, int *movement_length, int *racket_middle_left, int *racket_middle_right) {
    if (*ball_length == 23 || *ball_length == 1)
        (*movement_length) *= -1;
    if ((*ball_width + *movement_width) == 1 || (*ball_width + *movement_width) == 76)
        check_hit_ball(ball_width, movement_width, racket_middle_left, racket_middle_right);
    *ball_width+= *movement_width;
    *ball_length += *movement_length;
}

void check_hit_ball(int *ball_width, int *movement_width, int *racket_middle_left, int *racket_middle_right) {
    if ((*ball_width + *movement_width) == 77) {
        if (((*racket_middle_right) || ((*racket_middle_right)+1) || ((*racket_middle_right)-1)) == (*ball_width + *movement_width)) {
            *movement_width *= -1;
        } 
    }
    if ((*ball_width + *movement_width) == 1) {
        if ((*racket_middle_left) == (*ball_width + *movement_width)) {
            *movement_width *= -1;
        } 
    }
}

void output_field(int *field) {
    //clear();
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if (field[y*SIZE_FIELD_WIDTH+x] == 1) {
                printf("#");
            } else if (field[y*SIZE_FIELD_WIDTH+x] == 2) {
                printf("o");
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