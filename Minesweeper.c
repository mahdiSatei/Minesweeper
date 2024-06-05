// Minesweeper Project 
// By Mahdi Sateei
// Enjoy playing and good luck :)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 20

int mines;
int row, col;
char name[max];
int i , j;

// Function declarations
void initializeBoard(char board[row][col], char realBoard[row][col]);
void placeMines(char realBoard[row][col]);
void countAdjacentMines(char realBoard[row][col]);
void expandZeroCells(char board[row][col], char realBoard[row][col], int x, int y);
int checkWin(char board[row][col]);
void handlePlayerMove(char board[row][col], char realBoard[row][col], int *mines, int start_time);

int printArr(int x, int y, char matrix[x][y]);
int select_difficulty();

int main()
{   
    srand(time(NULL));
    while (1)
    {   
        int x , y;
        int start_time = time(NULL);

        // Selecting game difficulty
        select_difficulty();
      
        // Creating two arrays: one for showing to the client, the other for mines and numbers
        char board[row][col];
        char realBoard[row][col];

        // Initialize the boards
        initializeBoard(board, realBoard);

        // Print the board and start the game
        printArr(row, col, board);

        // Ensure the first move is never a mine
        while(1){
            printf("\nRemainder Mines : %d\n", mines);
            printf("Enter Your Move -> (x,y)\n");
            scanf("%d %d", &x, &y);
            if(x >= row || y >= col){
                printf("\t\nOops!\t\nYou Entered The Wrong Key! Please Try Again.\n\n");
                continue;
            }
            board[x][y] = realBoard[x][y];
            break;
        }

        // Place the mines randomly on the board
        placeMines(realBoard);

        // Count the number of mines in the adjacent cells
        countAdjacentMines(realBoard);

        // Show the content of the cell that the client selected
        board[x][y] = realBoard[x][y];
        if(board[x][y] == '0'){
            expandZeroCells(board, realBoard, x, y);
        }

        printArr(row, col, board);

        // Game loop
        while (1)
        {   
            if(checkWin(board)){
                printf("\t\nYou've Won %s :)\t\nIt Took %ds\n", name, time(NULL) - start_time);
                break;
            }
            handlePlayerMove(board, realBoard, &mines, start_time);
            printArr(row, col, board);
        }
        printArr(row, col, realBoard);
        break;
    }
}

void initializeBoard(char board[row][col], char realBoard[row][col]) {
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            board[i][j] = '-';
            realBoard[i][j] = '0';
        }
    }
}

void placeMines(char realBoard[row][col]) {
    int mines_count = 0;
    while (mines_count < mines) {   
        int minesRow = rand() % row;
        int minesCol = rand() % col;
        if(realBoard[minesRow][minesCol] == '*' || realBoard[minesRow][minesCol] == '-')
            continue;
        realBoard[minesRow][minesCol] = '*';
        mines_count++;
    }
}

void countAdjacentMines(char realBoard[row][col]) {
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (realBoard[i][j] != '*') {
                for(int ii = -1; ii < 2; ii++) {
                    for(int jj = -1; jj < 2; jj++) {
                        if(i + ii >= 0 && j + jj >= 0 && i + ii < row && j + jj < col) {
                            if(realBoard[ii + i][jj + j] == '*')
                                realBoard[i][j]++;
                        }
                    }
                }
            }
        }
    }
}

void expandZeroCells(char board[row][col], char realBoard[row][col], int x, int y) {
    int change = 1;
    while(change) {
        change = 0;
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(board[i][j] == '0') {
                    for(int ii = -1; ii < 2; ii++) {
                        for(int jj = -1; jj < 2; jj++) {
                            if(i + ii >= 0 && j + jj >= 0 && i + ii < row && j + jj < col) {
                                if(realBoard[i + ii][j + jj] == '0' && board[i + ii][j + jj] == '-')
                                    change = 1;
                                board[i + ii][j + jj] = realBoard[i + ii][j + jj];
                            }
                        }
                    }
                }
            }
        }
    }
}

int checkWin(char board[row][col]) {
    if(mines == 0) {
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(board[i][j] == '-') {
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}

void handlePlayerMove(char board[row][col], char realBoard[row][col], int *mines, int start_time) {
    int x, y;
    char bombeInput;
    printf("Remainder Mines : %d\n", *mines);
    printf("Enter Your Move -> (x,y)\n");
    scanf("%d %d", &x, &y);
    if(x >= row || y >= col) {
        printf("\t\nOops!\t\nYou Entered The Wrong Key! Please Try Again.\n");
        return;
    }

    printf("Press ? For Flag\nPress ! For Continue\n");
    scanf(" %c", &bombeInput);
    if (bombeInput == '?') {   
        if(board[x][y] == '?') {
            (*mines)++;
            board[x][y] = '-';
        } else {
            board[x][y] = '?';
            (*mines)--;
        }
    } else if (bombeInput == '!') {   
        if(realBoard[x][y] == '*') {
            printf("\t\nOops :( You've Lost! \t\nIt Took %ds\n", time(NULL) - start_time);
            exit(0);
        } else {
            board[x][y] = realBoard[x][y];
            if(board[x][y] == '0') {
                expandZeroCells(board, realBoard, x, y);
            }
        }
    } else {
        printf("\t\nOops!\t\nYou Entered The Wrong Key! Please Try Again.\n");
    }
}

int select_difficulty() {
    int input;
    printf("please Enter Your Name : ");
    gets(name);
    
    while (1) {
        printf("\t\nWelcome %s :)\t\n\nPlease Select Game Difficulty.\t\n\nPress 0 for Beginner ( 10 mines And 9x9 Titles )\t\n\nPress 1 for Intermediate ( 40 mines And 16x16 Titles )\t\n\nPress 2 for Advanced ( 99 mines And 30x16 Titles )\n\n", name);
        
        scanf("%d", &input);
        
        switch (input) {
        case 0:
            col = 9;
            row = col;
            mines = 10;
            break;
        case 1:
            col = 16;
            row = col;
            mines = 40;
            break;
        case 2:
            col = 30;
            row = 16;
            mines = 99;
            break;
        default:
            printf("\t\nOops!\t\nYou Entered The Wrong Key! Please Try Again.\n");
            continue;
        }
        break;
    }
    return 0;
}

int printArr(int x, int y, char matrix[x][y]) {
    printf("\t     ");
    for (j = 0; j < y; j++) {
        if (j < 10) {
            printf("%d  ", j);
        } else {
            printf("%d ", j);
        }
    }
    printf("\n\t     ");
    for (j = 0; j < y; j++) {
        printf("=  ");
    }

    printf("\n");

    for (i = 0; i < x; i++) {   
        if (i < 10) {
            printf("\t %d | ", i);
        } else {
            printf("\t%d | ", i);
        }
        
        for (j = 0; j < y; j++) {   
            printf("%c  ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

