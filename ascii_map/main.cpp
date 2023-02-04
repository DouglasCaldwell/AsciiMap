#include <iostream>
#include <fstream>

using namespace std;
#define sidelength 15
#define board_of_games "src/gameboard.txt"
#define file_of_saves "src/savefile.txt"


void initialize(string filename, char* board);
void open_save(string savefile, int* pos);
void display(char* board, int* pos);
void character_move(char* board, int* pos);
void save_files(int* pos);


int main() {
    char board[1000];
    char* ptr_board = board;
    int char_pos[2] = {0, 0};
    initialize(board_of_games, ptr_board);
    open_save(file_of_saves, char_pos);
    display(ptr_board, char_pos);
    character_move(ptr_board, char_pos);
    return 0;
}

/*
 * opens file
 * outputs to an array
 * returns array location to main
 */
void initialize(string filename, char* board) {
    ifstream game;
    game.open(filename, ios::in);
    if (!game) {
        cout << "File not opened" << endl;
    } else {
        cout << "Game starting!" << endl;
        int i = 0;
        while (!game.eof()) {
            game >> board[i];
            i++;
        }
    }
    game.close();
}

/*
 * loads where player is
 */
void open_save(string savefile, int* pos) {
    ifstream pers;
    pers.open(savefile, ios::in);
    if (!pers) {
        cout << "File not opened" << endl;
    } else {
        string temp;
        for (int k = 0; k < 2; k++) {
            getline(pers, temp);
            pos[k] = stoi(temp, 0, 10);
        }
        cout << "Game started!" << endl;
    }
    pers.close();
}

/*
 * Displays current game board
 */
void display(char* board, int* pos){
    int printer;
    int char_x = pos[0];
    int char_y = pos[1];
    for (int i=0; i<sidelength; i++) {
        cout << '\n';
        for (int j = 0; j < sidelength; j++) {
            if (char_y == i && char_x == j){
                cout << "@ ";
            } else {
                printer = sidelength * i + j;
                cout << board[printer] << " ";
            }
        }
    }
}

void character_move(char* board, int* pos) {
    char move;
    int flag = 0;
    cin >> move;
    if (move == 'w') {
        if (pos[1] == 0) {
            cout << "Can't move there!" << endl;
            flag = 1;
        } else pos[1]--;
    } else if (move == 's') {
        if (pos[1] == sidelength-1) {
            cout << "Can't move there!" << endl;
            flag = 1;
        } else pos[1]++;
    } else if (move == 'a') {
        if (pos[0] == 0) {
            cout << "Can't move there!" << endl;
            flag = 1;
        } else pos[0]--;
    } else if (move == 'd') {
        if (pos[0] == sidelength-1) {
            cout << "Can't move there!" << endl;
            flag = 1;
        } else pos[0]++;
    } else {
        cout << "invalid input, do you want to exit? (y)" << endl;
        flag = 2;
    }
    if (flag == 0) {
        display(board, pos);
        character_move(board, pos);
    } else if (flag == 1) {
        character_move(board, pos);
    } else if (flag == 2) {
        char exit;
        cin >> exit;
        if (exit == 'y') {
            save_files(pos);
        } else {
            cout << "Returning to game, use 'WASD' to move" << endl;
            character_move(board, pos);
        }
    }
}

void save_files(int* pos){
    ofstream pers;
    pers.open(file_of_saves, ios::out);
    if (!pers) {
        cout << "File not opened, Game not saved" << endl;
    } else {
        pers << pos[0] << '\n' << pos[1];
        cout << "Game closed successfully!" << endl;
    }
    pers.close();
}