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
#define START_BALL_LEFT_PLAYER 2
#define START_BALL_RIGHT_PLAYER 77

void paint_field(int *field, int *movement_width, int *movement_length);
int input();
void output_field(int *field);
int input_racket_left(int racket_move);
int input_racket_right(int racket_move);
void clear();
void move_ball(int *filed, int *movement_width, int *movement_length);
void check_hit_ball(int *filed, int *movement_width);
void check_point(int *field, int *point_left_player, int *point_right_player);
void output_count_players(int *count, int *point_left_player, int *point_right_player);
void start_new_game(int *field, int res);
void start_field(int *field);
void update_racket(int *field, int middle_racket_left, int middle_racket_right);
void update_ball(int *field, int ball_width, int ball_length, int *movement_width, int *movement_length);

int main() {
    int field[SIZE_FIELD_WIDTH][SIZE_FIELD_LENGTH];
    int racket_middle_left = 12;
    int racket_middle_right = 12;
    int ball_width = 2, ball_length = 12;
    int movement_width = 1, movement_length = 1;
    int count = 0, point_left_player = 0, point_right_player = 0;
    start_field(&field[0][0]);
    while(count != 21) {
        output_count_players(&count, &point_left_player, &point_right_player);
        paint_field(&field[0][0], &movement_width, &movement_length);
        
        
        
        //paint_field(&racket_middle_left, &racket_middle_right, &ball_width, &ball_length, &field[0][0]);
        //start_field(&field[0][0]);
        //printf("racket left: %d, racket right: %d, ball width: %d, ball length: %d\n", racket_middle_left, racket_middle_right, ball_width, ball_length);
        
        //move_ball(&ball_width, &ball_length, &movement_width, &movement_length, &racket_middle_left, &racket_middle_right);
        //check_point(&field[0][0], &point_left_player, &point_right_player);
    }
    return 0;
}

void start_field(int *field) {
    //0 - пробел
    //1 - границы вверх, низ, лево, право
    //2 - мяч
    //3 - ракетка
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if ((y == TOP_BIRDER) || (y == BOTTOM_BIRDER)) { //вверх или низ
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else if ((x == LEFT_BIRDER) || (x == RIGHT_BIRDER)) { //лево или право
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else if (x == (RIGHT_BIRDER/2) && ((y%2) == 0)) { //середина поля
                field[y*SIZE_FIELD_WIDTH+x] = 1;
            } else if ((x == START_RACKET_LEFT) && ((y == MIDDLE_FIELD_LENGTH) ||
              (y == MIDDLE_FIELD_LENGTH - 1) || (y == MIDDLE_FIELD_LENGTH + 1))) { // левая ракетка
                field[y*SIZE_FIELD_WIDTH+x] = 3;
            } else if ((x == START_RACKET_RIGHT) && ((y == MIDDLE_FIELD_LENGTH) ||
              (y == MIDDLE_FIELD_LENGTH - 1) || (y == MIDDLE_FIELD_LENGTH + 1))) { // правая ракетка
                field[y*SIZE_FIELD_WIDTH+x] = 4;
            } else if ((x == START_BALL_LEFT_PLAYER) && (y == MIDDLE_FIELD_LENGTH)) { //мяч у левого игрока
                field[y*SIZE_FIELD_WIDTH+x] = 2;
            } else {
                field[y*SIZE_FIELD_WIDTH+x] = 0;
            }
        }
    }
}

void paint_field(int *field, int *movement_width, int *movement_length) {
    int middle_racket_left, middle_racket_right;
    int ball_width, ball_length;
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            switch (field[y*SIZE_FIELD_WIDTH+x]) {
                case 2: {
                    ball_width =x; 
                    ball_length = y;
                    } break;
                case 3: {
                    if (((field[(y-1)*SIZE_FIELD_WIDTH+x]) == 3) 
                        && (((field[(y+1)*SIZE_FIELD_WIDTH+x]) == 3))) 
                        middle_racket_left = y; 
                    } break;
                case 4: if (((field[(y-1)*SIZE_FIELD_WIDTH+x]) == 4) 
                        && (((field[(y+1)*SIZE_FIELD_WIDTH+x]) == 4))) 
                        middle_racket_right = y; break;
                default: break;
            }
        }
    }
    output_field(field);
    update_racket(field, middle_racket_left, middle_racket_right);
    update_ball(field, ball_width, ball_length, movement_width, movement_length);

}

void update_ball(int *field, int ball_width, int ball_length, int *movement_width, int *movement_length) {
    //field[ball_width*SIZE_FIELD_WIDTH+ball_length] = 0;
    move_ball(field, movement_width, movement_length);

}

void update_racket(int *field, int middle_racket_left, int middle_racket_right) {
    
    field[middle_racket_left*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 0;
    field[(middle_racket_left-1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 0;
    field[(middle_racket_left+1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 0;

    field[middle_racket_right*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 0;
    field[(middle_racket_right-1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 0;
    field[(middle_racket_right+1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 0;
    
    middle_racket_left = input_racket_left(middle_racket_left);
    middle_racket_right = input_racket_right(middle_racket_right);

    field[middle_racket_left*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 3;
    field[(middle_racket_left-1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 3;
    field[(middle_racket_left+1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 3;

    field[middle_racket_right*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 4;
    field[(middle_racket_right-1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 4;
    field[(middle_racket_right+1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 4;
    
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

void move_ball(int *field, int *movement_width, int *movement_length) {
    int ball_length, ball_width;
    int middle_racket_left, middle_racket_right;
    int racket_middle_left, racket_middle_right;
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            switch (field[y*SIZE_FIELD_WIDTH+x]) {
                case 2: {
                    ball_width =x; 
                    ball_length = y;
                    } break;
                case 3: {
                    if (((field[(y-1)*SIZE_FIELD_WIDTH+x]) == 3) 
                        && (((field[(y+1)*SIZE_FIELD_WIDTH+x]) == 3))) 
                        middle_racket_left = y; 
                    } break;
                case 4: if (((field[(y-1)*SIZE_FIELD_WIDTH+x]) == 4) 
                        && (((field[(y+1)*SIZE_FIELD_WIDTH+x]) == 4))) 
                        middle_racket_right = y; break;
                default: break;
            }
        }
    }
    field[ball_length*SIZE_FIELD_WIDTH+ball_width] = 0;
    printf("ball width: %d ball length: %d\n", ball_width, ball_length);
    ball_width+= *movement_width;
    ball_length += *movement_length;
    field[ball_length*SIZE_FIELD_WIDTH+ball_width] = 2;
    if (ball_length == 23 || ball_length == 1)
        (*movement_length) *= -1;
    if ((ball_width + (*movement_width)) == 1 || (ball_width + (*movement_width)) == 78)
        check_hit_ball(field, movement_width);

}

void check_hit_ball(int *field, int *movement_width) {
    int res = 0;
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            switch (field[y*SIZE_FIELD_WIDTH+x]) {
                case 2: {                    
                     if (((field[(y)*SIZE_FIELD_WIDTH+(x-1)]) == 3) || 
                         ((field[(y)*SIZE_FIELD_WIDTH+(x+1)]) == 4)){
                             res = 1;
                         }
                    } break;
                default: break;
            }
        }
    }
    if (res != 0) {
        *movement_width *= -1;
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
        case 0: { res = 2; printf("*******POINT LEFT PLAYER*******\n"); (*point_left_player)++; start_new_game(field, res);} break;
        case 78: { res = 1; printf("*******POINT RIGHT PLAYER*******\n"); (*point_right_player)++; start_new_game(field, res);} break;
        default: { res = 0; } break;
    }
    printf("RESULT: %d\n", res);
}

void output_count_players(int *count, int *point_left_player, int *point_right_player) {
    printf("---------------------------------------------------------------------------------\n");
    printf("\t\t\t\tcount: %d\n\tpoint left player: %d\t\t\tpoint right player: %d\n", *count, *point_left_player, *point_right_player);
}

void start_new_game(int *field, int res) {
    switch (res) {
    case 2: {
        int y = START_BALL_LEFT_PLAYER;
        int x = MIDDLE_FIELD_LENGTH;
        field[y*SIZE_FIELD_WIDTH+x] = 2;
        } break;
    case 1: {
        int y = START_BALL_RIGHT_PLAYER;
        int x = MIDDLE_FIELD_LENGTH;
        field[y*SIZE_FIELD_WIDTH+x] = 2;
        } break;
    default: break;
    }
}

void output_field(int *field) {
    //clear();
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            switch (field[y*SIZE_FIELD_WIDTH+x]) {
                case 0: printf(" "); break;
                case 1: printf("#"); break;
                case 2: printf("o"); break;
                case 3: printf("#"); break;
                case 4: printf("#"); break;
                default: break;
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