#include <iostream>

using namespace std;

void greetAndInstruct()
{
    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer.\n";
    cout << "The board is numbered from 1 to 27 as per the following:\n";
    cout << "     1 | 2 | 3     10 | 11 | 12     19 | 20 | 21\n";
    cout << "     -------------------------------------------\n";
    cout << "     4 | 5 | 6     13 | 14 | 15     22 | 23 | 24\n";
    cout << "     -------------------------------------------\n";
    cout << "     7 | 8 | 9     16 | 17 | 18     25 | 26 | 27\n";
    cout << "Player starts first. Simply input the number of the cell you want to occupy.\n";
    cout << "Player’s move is marked with X. Computer’s move is marked with O.\n";
    cout << "\n";
    cout << "Start? (y/n):";
    char startVar;
    cin >> startVar; // get input and store in startVar
    if (startVar == 'y') {
        //start game
        cout << "Let's Begin\n";
        return;
    } else if (startVar == 'n') {
        exit(EXIT_SUCCESS);
    } else {
        cout << "Answer not recognised";
        exit(EXIT_SUCCESS);
    }
}

void displayBoard(char board[]) 
{
    // for each row
    for (int j=0; j<=6; j+=3) {
        cout << "\t";
        // for cols of first table
        for (int i=0; i<3; i++) {
            if (board[j+i] == 79){
                cout << 'O';
            } else if (board[j+i] == 88) { 
                cout << 'X';
            } else {
                cout << (int)board[j+i];
            }
            if (i != 2) {
                cout  << " | ";
            }
        }
        cout << "\t";
        // for cols of second table
        for (int i=9; i<12; i++) {
            if (board[j+i] == 79){
                cout << 'O';
            } else if (board[j+i] == 88) { 
                cout << 'X';
            } else {
                cout << (int)board[j+i];
            }
            if (i != 11) {
                cout  << " | ";
            }
        }
        cout << "\t";
        // for cols of third table
        for (int i=18; i<21; i++) {
            if (board[j+i] == 79){
                cout << 'O';
            } else if (board[j+i] == 88) { 
                cout << 'X';
            } else {
                cout << (int)board[j+i];
            }
            if (i != 20) {
                cout  << " | ";
            }
        }
        // for row dividers
        cout << "\n";
        if (j != 6) {
            cout << "\t---------\t------------\t------------\n";
        }
    }
}

bool checkIfLegal (int cellNbre, char board[]) 
{
    // possible number on board
    if(cellNbre > 26) {
        return false;
    } else {
        // check if cell is empty
        int cell = (int)board[cellNbre];
        if (cell == cellNbre+1) {
            return true;
        } else {
            return false;
        }
    }
}

bool checkWinner(char board[]) 
{
    for (int i=0; i<25; i+=3) {
        // rows (2D)
        if(board[i]==board[i+1] && board[i+1]==board[i+2]) { 
            return true;
        }
    }
    for (int i=0; i<19; i+=9) {
        // cols (2D)
        for (int j=0; j<3; j++) {
            if(board[i+j]==board[i+j+3] && board[i+j+3]==board[i+j+6]) { 
                return true;
            }
        }
        //diagonals (L->R) (2D)
        if(board[i]==board[i+4] && board[i+4]==board[i+8]) { 
            return true;
        }
    }
    for (int i=2; i<21; i+=9) {
        //diagonals (R->L) (2D)
        if(board[i]==board[i+2] && board[i+2]==board[i+4]) { 
            return true;
        }
    }
    // check all overlap verticals (3D)
    for (int j=0; j<9; j++) {
        if (board[j]==board[j+9] && board[j+9]==board[j+18]) {
            return true;
        }
    }
    for (int i=0; i<7; i+=3) {
        // horizontal diagonal (L->R) (3D)
        if(board[i]==board[i+10] && board[i+10]==board[i+20]) { 
            return true;
        }
        // horizontal diagonal (R->L) (3D)
        if(board[i+2]==board[i+10] && board[i+10]==board[i+18]) { 
            return true;
        }
    }
    for (int i=0; i<3; i++) {
        // vertical diagonal (T->D) (3D)
        if(board[i]==board[i+12] && board[i+12]==board[i+24]) { 
            return true;
        }
        // vertical diagonal (D->T) (3D)
        if(board[i+6]==board[i+12] && board[i+12]==board[i+18]) { 
            return true;
        }
    }
    // check 1st diagonal in both directions (3D)
    if(board[0]==board[13] && board[13]==board[26]) {
        return true;
    }
    if(board[8]==board[13] && board[13]==board[18]) {
        return true;
    }
    // check 2nd diagonal in both directions (3D)
    if(board[2]==board[13] && board[13]==board[24]) {
        return true;
    }
    if(board[6]==board[13] && board[13]==board[20]) {
        return true;
    }
    // if we get down here and nothing got caught, there is no winner yet
    return false;
}

void addMove(int cellNbre, int player, char board[])
{
    if (player == 0) {
        board[cellNbre] = 88;
    } else {
        board[cellNbre] = 79;
    }
}

void delMove(int cellNbre, char board[])
{
    board[cellNbre] = cellNbre+1;
}

void computerMove(char board[])
{
    // copy temp board to manipulate
    char temp[27];
    for (int j=0; j<27; j++) {
        temp[j] = board[j];
    }
    // if play will make computer a winner -- win
    for (int i=0; i<27; i++) {
        if (checkIfLegal(i, temp)) {
            addMove(i, 0, temp);
            if (checkWinner(temp)) {//says @ i = 5 that it will make computer a winner
                addMove(i, 0, board);
                return;
            } else {
                delMove(i, temp);
            }
        }
    }
    // if play will make player a winner -- block
    for (int i=0; i<27; i++) {
        if (checkIfLegal(i, temp)) {
            addMove(i, 1, temp);
            if (checkWinner(temp)) {
                addMove(i, 0, board);
                return;
            } else {
                delMove(i, temp);
            }
        }
    }
    // if no strategic move -- choose 1st possible cell 
    for (int i=0; i<27; i++) {
        if (checkIfLegal(i, board)) {
            addMove(i, 0, board);
            return;
        }
    }
}


