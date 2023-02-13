#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;
#define height 14
#define width 30
#define board_of_games "src/gameboard.txt"
#define file_of_saves "src/savefile.txt"
#define short_delay 150


int startgame();
void initialize(string filename, char* board);
void open_save(string savefile, int* pos);
void new_board(char* board, int* pos);
void display(char* board, int* pos);
void character_move(char* board, int* pos);
void save_files(char* board, int* pos);
bool blocker(char* board, int* pos);

int main() {
    system("cls");
    char board[1000];
    char* ptr_board = board;
    int char_pos[2] = {0, 0};
    int start = startgame();
    if (start==2){
        new_board(ptr_board, char_pos);
    } else if (start==1){
        initialize(board_of_games, ptr_board);
        open_save(file_of_saves, char_pos);
    } else {
        return 0;
    }
    display(ptr_board, char_pos);
    character_move(ptr_board, char_pos);
    return 0;
}

int startgame(){
    cout << "Would you like to load your old game?(y/n)" <<endl;
    char load;
    cin >> load;
    cin.clear();
    if (load == 'y'){
        cout << "Booting up" << endl;
        return 1;
    } else {
        cout << "Would you like to start a new game?(y) \n Bear in mind this will wipe the old save." <<endl;
        cin >> load;
        cin.clear();
        if (load == 'y') {
            cout << "Starting new game" << endl;
            return 2;
        } else {
            return 0;
        }
    }
}

void new_board(char* board, int* pos) {
    int startline = (width - 20) / 2;
    for (int i = 0; i <= startline; i++) {
        board[i] = '~';
    }
    char temp[25] = "ASCIIMAP-GAME-PLAYER_A";
    for (int j = 0; j < 25; j++) {
        board[startline + j] = temp[j];
    }
    for (int k = (width - startline); k < width; k++) {
        board[k] = '~';
    }
    board[width] = '\n';
    for (int l = width; l < 2 * width; l++) {
        board[l] = '.';
    }
    board[2 * width] = '\n';
    int randtime;
    srand(time(nullptr));
    for (int m = 2 * width; m <= height * width; m++) {
        randtime = rand() % 15;
        if (randtime == 1 || randtime == 2) {
            board[m] = '^';
        } else if (randtime == 3 || randtime == 4) {
            board[m] = '_';
        } else if (randtime == 5) {
            board[m] = '*';
        } else {
            board[m] = '.';
        }
    }
    pos[0] = 0;
    pos[1] = 1;
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
        game.close();
    }
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
            pos[k] = stoi(temp, nullptr, 10);
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
    for (int i=0; i < height; i++) {
        cout << '\n';
        for (int j = 0; j < width; j++) {
            if (char_y == i && char_x == j){
                cout << "@ ";
            } else {
                printer = width * i + j;
                cout << board[printer] << " ";
            }
        }
    }
}

void character_move(char* board, int* pos) {
    int flag = 0;
    if (GetKeyState('W') & 0x8000) {
        if (pos[1] <= 1) {
            cout << "Can't move there!" << endl;
            Sleep(short_delay);
            flag = 0;
        } else {
            pos[1]--;
            if (!blocker(board, pos)) {
                cout << "There is an obstacle there" << endl;
                Sleep(short_delay);
                flag = 0;
                pos[1]++;
            } else {
                flag = 1;
            }
        }
    } else if (GetKeyState('S') & 0x8000) {
        if (pos[1] >= height - 1) {
            cout << "Can't move there!" << endl;
            Sleep(short_delay);
            flag = 0;
        } else {
            pos[1]++;
            if (!blocker(board, pos)) {
                cout << "There is an obstacle there" << endl;
                Sleep(short_delay);
                flag = 0;
                pos[1]--;
            } else {
                flag = 1;
            }
        }
    } else if (GetKeyState('A') & 0x8000) {
        if (pos[0] <= 0) {
            cout << "Can't move there!" << endl;
            Sleep(short_delay);
            flag = 0;
        } else {
            pos[0]--;
            if (!blocker(board, pos)) {
                cout << "There is an obstacle there" << endl;
                Sleep(short_delay);
                flag = 0;
                pos[0]++;
            } else {
                flag = 1;
            }
        }
    } else if (GetKeyState('D') & 0x8000) {
        if (pos[0] >= width - 1) {
            cout << "Can't move there!" << endl;
            Sleep(short_delay);
            flag = 0;
        } else {
            pos[0]++;
            if (!blocker(board, pos)) {
                cout << "There is an obstacle there" << endl;
                Sleep(short_delay);
                flag = 0;
                pos[0]--;
            } else {
                flag = 1;
            }
        }
    } else if (GetKeyState('E') & 0x8000) {
        cout << "E pressed for exit, do you want to exit? (y)" << endl;
        flag = 2;
    }
    if (flag == 0) {
        character_move(board, pos);
    } else if (flag == 1) {
        display(board, pos);
        Sleep(short_delay);
        character_move(board, pos);
    } else {
        char exit;
        cin >> exit;
        if (exit == 'y') {
            save_files(board, pos);
        } else {
            cout << "Returning to game, use 'WASD' to move" << endl;
            character_move(board, pos);
        }
    }
}

void save_files(char* board, int* pos) {
    ofstream pers;
    pers.open(file_of_saves, ios::out);
    if (!pers) {
        cout << "File not opened, Game not saved" << endl;
    } else {
        pers << pos[0] << '\n' << pos[1];
        cout << "Game closed successfully!" << endl;
    }
    pers.close();
    ofstream game;
    game.open(board_of_games, ios::out);
    if (!game) {
        cout << "File not opened, Board not saved" << endl;
    } else {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int place = i * width + j;
                game << board[place];
            }
            game << endl;
        }
    }
    game.close();
}

bool blocker(char* board, int* pos){
    bool empty = false;
    int space = (pos[0] + ((pos[1])*width));
    if (board[space]=='.'){
        empty = true;
    }
    return empty;
}