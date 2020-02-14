#include <iostream>
#include <limits>

using namespace std;

// assignment function declarations
void greetAndInstruct();
void displayBoard(char board[]);
bool checkIfLegal (int cellNbre, char board[]);
bool checkWinner(char board[]);
void computerMove(char board[]);

// helper function declarations
void addMove(int cellNbre, int player, char board[]);
void delMove(int cellNbre, char board[]);


int main()
{
    char board [27] { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 };
    int count = 0; // counts number of moves to distinguish tie
    greetAndInstruct();
    // computer = 0, player = 1
    // always use the array indices as the cellNbre not the cell label
    while (true) {
        //PLAYER TURN
        cout << "Choose a cell to put your marker: ";
        int cell;
        // dont let player make move unless valid and legal:
        bool legal = false;
        while (legal == false) {
            cin >> cell;
            if (cin.fail()){
                cout << "Not a valid input - Try an Integer: ";
                // clear error state
                cin.clear();
                // discard 'bad' character(s)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if (checkIfLegal(cell-1, board)) {
                // add move when legal
                addMove(cell-1, 1, board);
                legal = true;
                count += 1;
            } else {
                cout << "That cell is not available - Try another one: ";
            }
        }
        displayBoard(board);
        if (checkWinner(board)) {  // check winner after every move
            cout << "PLAYER WINS\n";
            exit(EXIT_SUCCESS);
        } else if (count >= 27) {  // check for tie after every move
            cout << "IT'S A TIE\n";
            exit(EXIT_SUCCESS);
        }
        
        //COMPUTER TURN
        computerMove(board);
        count += 1;
        cout << "\nComputer Move: \n";
        displayBoard(board);
        if (checkWinner(board)) { // check winner after every move
            cout << "COMPUTER WINS\n";
            exit(EXIT_SUCCESS);
        } else if (count >= 27) {  // check for tie after every move
            cout << "IT'S A TIE\n";
            exit(EXIT_SUCCESS);
        }
    }
}


