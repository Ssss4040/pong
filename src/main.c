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
void check_hit_ball(int *ball_width, int *movement_width,int *ball_length, int *movement_length, int *racket_middle_left, int *racket_middle_right);
void check_point(int *field, int *point_left_player, int *point_right_player);
void output_count_players(int *count, int *point_left_player, int *point_right_player);

int main() {
    int field[SIZE_FIELD_WIDTH][SIZE_FIELD_LENGTH];
    int racket_middle_left = 12;
    int racket_middle_right = 12;
    int ball_width = 2, ball_length = 12;
    int movement_width = 1, movement_length = 1;
    int count = 0, point_left_player = 0, point_right_player = 0;
    while(count != 21) {
        output_count_players(&count, &point_left_player, &point_right_player);
        paint_field(&racket_middle_left, &racket_middle_right, &ball_width, &ball_length, &field[0][0]);
        printf("racket left: %d, racket right: %d, ball width: %d, ball length: %d\n", racket_middle_left, racket_middle_right, ball_width, ball_length);
        move_ball(&ball_width, &ball_length, &movement_width, &movement_length, &racket_middle_left, &racket_middle_right);
        check_point(&field[0][0], &point_left_player, &point_right_player);
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
    if ((*ball_width + *movement_width) == 1 || (*ball_width + *movement_width) == 77)
        check_hit_ball(ball_width, movement_width, ball_length, movement_length, racket_middle_left, racket_middle_right);
    *ball_width+= *movement_width;
    *ball_length += *movement_length;
    
    //##################### DELETE ##############################################
    printf("ball_width: %d\t\tball_length: %d\n", *ball_width, *ball_length);
    printf("movement_width: %d\tmovement_length: %d\n", *movement_width, *movement_length);
    printf("CHECK HIT BALL-----------------------------------------\n");
    printf("(*ball_width) + (*movement_width)) = %d\n", (*ball_width) + (*movement_width));
    printf("----------------------RIGHT:\n");
    printf("((*racket_middle_right: (%d)) == (*ball_width(%d) + *movement_width(%d)))\n", (*racket_middle_right), (*ball_width), (*movement_width));
    printf("((*racket_middle_right+1: (%d)) == (*ball_width(%d) + *movement_width(%d)))\n", (*racket_middle_right)+1, (*ball_width), (*movement_width));
    printf("((*racket_middle_right-1: (%d)) == (*ball_width(%d) + *movement_width(%d)))\n", (*racket_middle_right)-1, (*ball_width), (*movement_width));
    printf("----------------------LEFT RACKET:\n");
    printf("((*racket_middle_left: (%d)) == (*ball_width(%d) + *movement_width(%d)))\n", (*racket_middle_left), (*ball_width), (*movement_width));
    printf("((*racket_middle_left+1: (%d)) == (*ball_width(%d) + *movement_width(%d)))\n", (*racket_middle_left)+1, (*ball_width), (*movement_width));
    printf("((*racket_middle_left-1: (%d)) == (*ball_width(%d) + *movement_width(%d)))\n", (*racket_middle_left)-1, (*ball_width), (*movement_width));
    printf("--------------------------------------------------------\n");
    //##################### DELETE ##############################################

}

void check_hit_ball(int *ball_width, int *movement_width,int *ball_length, int *movement_length, int *racket_middle_left, int *racket_middle_right) {
    if (((*ball_width) + (*movement_width)) == 77) {
        if (((*racket_middle_right) == (*ball_length + *movement_length))
        || (((*racket_middle_right)+1) == (*ball_length + *movement_length)) 
        || (((*racket_middle_right)-1) == (*ball_length + *movement_length))) {
            *movement_width *= -1;
        } 
    }
    if (((*ball_width) + (*movement_width)) == 1) {
        if (((*racket_middle_left) == (*ball_length + *movement_length))
        || (((*racket_middle_left)+1) == (*ball_length + *movement_length)) 
        || (((*racket_middle_left)-1) == (*ball_length + *movement_length))) {
            *movement_width *= -1;
        } 
    }
}

void check_point(int *field, int *point_left_player, int *point_right_player) {
    //никто не забил - return 0
    //левый игрок забил - return 1
    //правый игрок забил - return 2
    int res = 0, ball_l = 0;
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if(field[y*SIZE_FIELD_WIDTH+x] == 2) {
                ball_l = x;
                printf("x=%d\n", x);
            }
        }
    }
    switch(ball_l) {
        case 0: { res = 2; printf("*******POINT LEFT PLAYER*******\n"); (*point_left_player)++;} break;
        case 78: { res = 1; printf("*******POINT RIGHT PLAYER*******\n"); (*point_right_player)++;} break;
        default: { res = 0; } break;
    }
    printf("RESULT: %d\n", res);
}

void output_count_players(int *count, int *point_left_player, int *point_right_player) {
    printf("---------------------------------------------------------------------------------\n");
    printf("\t\t\t\tcount: %d\n\tpoint left player: %d\t\t\tpoint right player: %d\n", *count, *point_left_player, *point_right_player);
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