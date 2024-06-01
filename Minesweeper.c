// Minesweeper Project 
// By Mahdi Sateei
// Enjoy playing and good luck :)

#include <stdio.h>
#include <stdlib.h>

#define max 20

int mines;
int row, col;
char name[max];
int i , j;

// The Function that printing the game board
int printArr();
int select_difficulty();

int main()
{   
    // printf("please Enter Your Name : ");
    // gets(name);
    srand(time(NULL));
    while (1)
    {   
        int x , y;
        int input;
        int count = '0';
        char bombeInput;
        int minesRow , minesCol;

        // Selecting game difiiculty

        select_difficulty();
      
        //  Creating two arry 
        //  The first one is for showing to the clinet
        //  The second one contians mines and numbers

        char board[row][col];
        char realBoard[row][col];

        // All the index of arry will be '-' and show to the client

        for ( i = 0; i < row; i++)
        {
            for ( j = 0; j < col; j++)
            {
                board[i][j] = '-';
            }
        }

        // print the board and starting the game

        printArr(row , col , board);

        int start_time = time(NULL);

        // All the index of main arry will be zero

        for ( i = 0; i < row; i++)
        {
            for ( j = 0; j < col; j++)
            {
                realBoard[i][j] = '0';
            }
        }
        
        // This while is for the first move that will never be a mine

        while(1){

            // Take the input move
            printf("\nRemainder Mines : %d\n" , mines);
            printf("Enter Your Move -> (x,y)\n");
            scanf("%d %d" , &x , &y);
            if(x >= row || y >= col){
                printf("\t\nOops!\t\nYou Enter The Wrong Key! Please Try Again.\n\n");
                continue;
            }
 
            board[x][y] = realBoard[x][y];

            break;
        }

        int mines_count = 0;

        // This while place the mines randomly on the board

        while (mines_count < mines)
        {   
            // Continue until all random mines have been created.
            int minesRow = rand()%row;
            int minesCol = rand()%col;
            // Continue if there is a mine placed in the same cell before
            if(realBoard[minesRow][minesCol] == '*' || realBoard[minesRow][minesCol]=='-')
                continue;
            // Place the mine
            realBoard[minesRow][minesCol] = '*';
            mines_count++;
        }
        
        // A for to count the number of mines in the adjacent cells

        for ( i = 0; i < row; i++)
        {
            for ( j = 0; j < col; j++)
            {
                if (realBoard[i][j] != '*')
                {
                    for(int ii=-1; ii<2; ii++){
                        for(int jj=-1; jj<2; jj++){
                            if(i+ii>=0 && j+jj>=0 && i+ii<row && jj+j < col){
                                if(realBoard[ii+i][jj+j]=='*')
                                    realBoard[i][j]++;
                            }
                        }
                    }
                }
                
            }
        }
        // printArr(row , col , board);
        // Show contian of the cell that the clinet selected
        board[x][y] = realBoard[x][y];

          if(board[x][y] == '0'){
                        int change = 1;
                        while(change){
                            change = 0;
                            for(int i=0; i<row; i++){
                                for(int j=0; j<col; j++){
                                    if(board[i][j]=='0'){
                                        for(int ii=-1; ii<2; ii++){
                                            for(int jj=-1; jj<2; jj++){
                                                if(i+ii>=0 && j+jj>=0 && i+ii<row && jj+j < col){
                                                    if(realBoard[i+ii][j+jj]=='0' && board[i+ii][j+jj]=='-')
                                                        change = 1;
                                                    board[i+ii][j+jj] = realBoard[i+ii][j+jj];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

        printArr(row , col , board);
        
        int win = 0;
        // This while continues until the clinet win or lose
        while (1)
        {   
            if(mines == 0){
                win = 1;
                for(int i=0; i<row; i++){
                    for(int j=0; j<col; j++){
                        if(board[i][j]=='-'){
                            win = 0;
                        }
                    }
                }
            }
            // If the reminder mines equal to zero and clinet guess all the mines places correctly
            // The massage will be appear and game will be finish 
            if(win){
                printf("\t\nYou've Won %s :)\t\nIt Took %ds\n", name ,time(NULL)-start_time);
                break;
            }
            // Take the input move
            printf("Remainder Mines : %d\n" , mines);
            printf("Enter Your Move -> (x,y)\n");
            scanf("%d %d" , &x , &y);
            if(x >= row || y >= col){
                printf("\t\nOops!\t\nYou Enter The Wrong Key! Please Try Again.\n\n");
                continue;
            }
            
            printf("Press ? For Flag\nPress ! For Countinue\n");
            scanf(" %c" , &bombeInput);
            if (bombeInput == '?')
            {   
                // If the selected cell is already ? and the clinte want to retrun it
                if(board[x][y]=='?'){
                    mines++;
                    board[x][y] = '-';
                }
                else{
                    board[x][y] = '?';
                    mines--;
                }
                printArr(row , col , board);
                continue;
            }
            else if (bombeInput == '!')
            {   
                // If the client press ! for showing the cell contains
                // And the cell was a mine
                // The massage will be appear and game will be finish
                if(realBoard[x][y] == '*'){
                    printf("\t\nOops :( You've Lost! \t\nIt Took %ds\n", time(NULL)-start_time);
                break;
                } else {
                    board[x][y] = realBoard[x][y];
                    // If there are no mines around the chosen cell
                    // It continues until it reaches a cell that contains number 
                    if(board[x][y] == '0'){
                        int change = 1;
                        while(change){
                            change = 0;
                            for(int i=0; i<row; i++){
                                for(int j=0; j<col; j++){
                                    if(board[i][j]=='0'){
                                        for(int ii=-1; ii<2; ii++){
                                            for(int jj=-1; jj<2; jj++){
                                                if(i+ii>=0 && j+jj>=0 && i+ii<row && jj+j < col){
                                                    if(realBoard[i+ii][j+jj]=='0' && board[i+ii][j+jj]=='-')
                                                        change = 1;
                                                    board[i+ii][j+jj] = realBoard[i+ii][j+jj];
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    printArr(row , col , board);
                }
                continue;
            } 
            else {
                printf("\t\nOops!\t\nYou Enter The Wrong Key! Please Try Again.\n");
                continue;
            }
        }
        printArr(row , col , realBoard);
        break;
    }
}
int select_difficulty(){
    int input;
    printf("please Enter Your Name : ");
    gets(name);
    
    while (1)
    {
        printf("\t\nWelcom %s :)\t\n\nPlease Select Game Difficulty.\t\n\nPress 0 for Beginner ( 10 mines And 9x9 Titles )\t\n\nPress 1 for Intermediate ( 40 mines And 16x16 Titles )\t\n\nPress 2 for Advanced ( 99 mines And 30x16 Titles )\n\n" , name);
        
        scanf("%d", &input);
        
        switch (input)
        {
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
            printf("\t\nOops!\t\nYou Enter The Wrong Key! Please Try Again.\n");
            continue;
            break;
        }
        break;
    }
}
int printArr(int x, int y, char matrix[x][y])
{
    printf("\t     ");
    for ( j = 0; j < y; j++)
    {
        if (j < 10)
        {
            printf("%d  " , j);
        } else {
            printf("%d " , j);
        }
    }
    printf("\n\t     ");
    for ( j = 0; j < y; j++)
    {
        if (j < 10)
        {
            printf("=  ");
        } else {
            printf("=  ");
        }
    }

    printf("\n");

    for (i = 0; i < x; i++)
    {   
        if ( i < 10)
        {
            printf("\t %d | " , i);
        } else printf("\t%d | " , i);
        
        for (j = 0; j < y; j++)
        {   
            printf("%c  ", matrix[i][j]);
        }
        printf("\n");
    }
}