#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
void output_field(int *field);
void move_ball(int *filed, int *movement_width, int *movement_length);
void check_hit_ball(int *filed, int *movement_width);
void check_point(int *field, int *point_left_player, int *point_right_player);
void output_count_players(int *count, int *point_left_player, int *point_right_player);
void start_new_game(int *field, int res);
void start_field(int *field);
void update_racket(int *field, int middle_racket_left, int middle_racket_right);
void update_ball(int *field, int *movement_width, int *movement_length);
void pausedelay(int milli_seconds);

int main() {
    initscr();
    savetty();
    nonl();
    cbreak();
    noecho();
    timeout(1);
    leaveok(stdscr, TRUE);
    curs_set(0);
    int field[SIZE_FIELD_WIDTH][SIZE_FIELD_LENGTH];
    int movement_width = 1, movement_length = 1;
    int count = 0, point_left_player = 0, point_right_player = 0;
    start_field(&field[0][0]);
    while(count != 21) {
        clear();
        output_count_players(&count, &point_left_player, &point_right_player);
        paint_field(&field[0][0], &movement_width, &movement_length);
        check_point(&field[0][0], &point_left_player, &point_right_player);
        pausedelay(90000);
        
    }
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
    return 0;
}

void pausedelay(int milli_seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds) {}
}

void start_field(int *field) {
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
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            switch (field[y*SIZE_FIELD_WIDTH+x]) {
                case 3: {
                    if (((field[(y-1)*SIZE_FIELD_WIDTH+x]) == 3) 
                        && (((field[(y+1)*SIZE_FIELD_WIDTH+x]) == 3))) 
                        middle_racket_left = y; 
                    } break;
                case 4: {
                    if (((field[(y-1)*SIZE_FIELD_WIDTH+x]) == 4) 
                        && (((field[(y+1)*SIZE_FIELD_WIDTH+x]) == 4))) 
                        middle_racket_right = y; 
                }break;
                default: break;
            }
        }
    }
    output_field(field);
    update_racket(field, middle_racket_left, middle_racket_right);
    update_ball(field, movement_width, movement_length);

}

void update_ball(int *field, int *movement_width, int *movement_length) {
    move_ball(field, movement_width, movement_length);

}

void update_racket(int *field, int middle_racket_left, int middle_racket_right) {
    field[middle_racket_left*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 0;
    field[(middle_racket_left-1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 0;
    field[(middle_racket_left+1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 0;

    field[middle_racket_right*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 0;
    field[(middle_racket_right-1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 0;
    field[(middle_racket_right+1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 0;
    
    switch (getch()) {
    case 'A': {if (middle_racket_left != 2) middle_racket_left--; } break;
    case 'a': {if (middle_racket_left != 2) middle_racket_left--; } break;
    case 'z': {if (middle_racket_left != 22) middle_racket_left++; } break;
    case 'Z': {if (middle_racket_left != 22) middle_racket_left++; } break;

    case 'K': {if (middle_racket_right != 2) middle_racket_right--; } break;
    case 'k': {if (middle_racket_right != 2) middle_racket_right--; } break;
    case 'm': {if (middle_racket_right != 22) middle_racket_right++; } break;
    case 'M': {if (middle_racket_right != 22) middle_racket_right++; } break;
    default: break;
    }

    field[middle_racket_left*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 3;
    field[(middle_racket_left-1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 3;
    field[(middle_racket_left+1)*SIZE_FIELD_WIDTH+START_RACKET_LEFT] = 3;

    field[middle_racket_right*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 4;
    field[(middle_racket_right-1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 4;
    field[(middle_racket_right+1)*SIZE_FIELD_WIDTH+START_RACKET_RIGHT] = 4;
    
}

void move_ball(int *field, int *movement_width, int *movement_length) {
    int ball_length, ball_width;
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            switch (field[y*SIZE_FIELD_WIDTH+x]) {
                case 2: {
                    ball_width =x; 
                    ball_length = y;
                    } break; 
                default: break;
            }
        }
    }
    field[ball_length*SIZE_FIELD_WIDTH+ball_width] = 0;
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
    int res = 0, ball_width = 0, ball_length = 0;
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            if(field[y*SIZE_FIELD_WIDTH+x] == 2) {
                ball_width = x;
                ball_length = y;
            }
        }
    }
    switch(ball_width) {
        case 0: { 
            res = 2; 
            (*point_left_player)++;
            field[ball_length*SIZE_FIELD_WIDTH+ball_width] = 1;
            start_new_game(field, res);
            } break;
        case 79: { 
            res = 1; 
            field[ball_length*SIZE_FIELD_WIDTH+ball_width] = 1; 
            (*point_right_player)++; 
            start_new_game(field, res);
            } break;
        default: { res = 0; } break;
    }
}

void output_count_players(int *count, int *point_left_player, int *point_right_player) {
    *count = *point_left_player + *point_right_player;
    printw("\t\t\t\tTOTAL SCORE: %d\n\tpoint left player: %d\t\t\tpoint right player: %d\n", *count, *point_left_player, *point_right_player);
}

void start_new_game(int *field, int res) {
    switch (res) {
    case 1: {
        int y = START_BALL_LEFT_PLAYER;
        int x = MIDDLE_FIELD_LENGTH;
        field[x*SIZE_FIELD_WIDTH+y] = 2;
        } break;
    case 2: {
        int y = START_BALL_RIGHT_PLAYER;
        int x = MIDDLE_FIELD_LENGTH;
        field[x*SIZE_FIELD_WIDTH+y] = 2;
        } break;
    default: break;
    }
    start_field(field);
}

void output_field(int *field) {
    for (int y = 0; y < SIZE_FIELD_LENGTH; y++) {
        for (int x = 0; x < SIZE_FIELD_WIDTH; x++) {
            switch (field[y*SIZE_FIELD_WIDTH+x]) {
                case 0: printw(" "); break;
                case 1: printw("#"); break;
                case 2: printw("o"); break;
                case 3: printw("#"); break;
                case 4: printw("#"); break;
                default: break;
            }
        }
        if (y != RIGHT_BIRDER) {
            printw("\n");
        }
    }
}
