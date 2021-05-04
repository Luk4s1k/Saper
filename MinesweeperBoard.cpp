//
// Created by Luka Mitrović on 23/03/2021.
//
#include <iostream>
#include "MinesweeperBoard.h"



Field::Field(){}

Field::Field(unsigned short int a, unsigned short int b){
    if(a == 0 && b == 0){
        this->hasMine = true;
        this->hasFlag = false;
        this->isRevealed =false;
    }else if(a == 1 && b == 1){
        this->hasMine = false;
        this->hasFlag = false;
        this->isRevealed = true;
    }else if(a == 2 && b == 0){
        this->hasMine = true;
        this->hasFlag = true;
        this->isRevealed = false;
    }else {
        hasMine = false;
        hasFlag = false;
        isRevealed = false;
    }
}

Field::Field(bool setMine) {
    this->hasMine = setMine;
}

//Create an empty field
MinesweeperBoard::MinesweeperBoard(int width, int height) :
        width(width), height(height),firstMove(false),mineCount(0) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            board[i][j].hasMine = false;
            board[i][j].hasFlag = false;
            board[i][j].isRevealed = false;
        }
    }
}
// Create a field with give gameMode
MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode) :
        width(width), height(height), mode(mode),firstMove(true),mineCount(0),gameState(RUNNING) {

    // Fill the board with empty fields
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            //Create and empty Field with no mines
            Field tempField(3, 3);
            this->board[i][j] = tempField;
        }
    }

    // Setting the GameMode
    int perDivider = 1;                             //Divider to calculate percentage
    if (mode == EASY) { perDivider = 10; mineCount = (height*width) / perDivider; }
    else if (mode == NORMAL) { perDivider = 5; mineCount = (height*width) / perDivider; }
    else if (mode == HARD) { perDivider = 3; mineCount = (height*width) / perDivider; }
    else if (mode == DEBUG) {                       // User sets the percentage of the board filling
        std::cout << "Enter the percentage: ";
        std::cin >> perDivider;
        perDivider = 100 / perDivider;
        mineCount = (height*width) / perDivider;
    }

    // Filling the field according to set percentage
    for (int i = 0; i <= (height * width) / perDivider; ++i) {
        createRandomMine();
    }

}
// Create a random Board and fill in the fields
void MinesweeperBoard::createBoard(MinesweeperBoard& mb){
    for(int i = 0; i < 10;++i){
        for (int j = 0; j < 10;++j){
            // Create a random field type
            Field tempField(rand()%3,rand()%2);
            mb.board[i][j] = tempField;
        }
    }
}

void MinesweeperBoard::debug_display(MinesweeperBoard &mb) const{
    // Default Empty Field representation
    char field_debug[6] = "[...]";

    for(int i = 0; i < mb.height;++i){
        for(int j = 0; j < mb.width; ++j){
            // Set the marker if the mine is present
            switch((int)mb.board[i][j].hasMine){
                case true: field_debug[1] = 'M';
                    break;
                case false: field_debug[1] = '.';
                    break;
            }
            // Set the marker if the field is revealed
            switch((int)mb.board[i][j].isRevealed){
                case true: field_debug[2] = 'o';
                    break;
                case false: field_debug[2] = '.';
                    break;
            }
            // Set the marker if the flag is set
            switch((int)mb.board[i][j].hasFlag){
                case true: field_debug[3] = 'F';
                    break;
                case false: field_debug[3] = '.';
                    break;
            }
            for(int k = 0; k < 6; ++k){
                std::cout << field_debug[k];
            }
        }
        std::cout << std::endl;
    }
}

int MinesweeperBoard::getBoardWidth() const {
    return this->width;
}

int MinesweeperBoard::getBoardHeight() const {
    return this->height;
}

int MinesweeperBoard::getMineCount() const {
    return this->mineCount;
}

int MinesweeperBoard::countMines(int row, int col) const {
    int mineCounter = 0;
    // Check for index to be within the boundaries
    if((row > this->height || row < 0) || (col > this->width || col < 0))
        return -1;
    //Check the field to be revealed
    if(!(this->board[row][col].isRevealed))
        return -1;
    // Loop counts mines around the given point
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j){
            if((j < 0) || (i < 0))continue;
            else {
                if(board[i][j].hasMine) mineCounter++;
            }

        }
    }
    return mineCounter;
}

// If field has flag return true
// If Field out of range return false
// If Field revealed return false
// If there is no flag return false
bool MinesweeperBoard::hasFlag(int row, int col) const {
    if(this->board[row][col].hasFlag){
        return true;
    }
    else{
        return false;
    }

    if((row > this->height || row < 0) || (col > this->width || col < 0)){
        return false;
    }

    if(this->board[row][col].isRevealed){
        return false;
    }
}

// If Field not revealed and has no flag put flag on it
// If field not revealed and has flag remove the flag
// If Field revealed do nothing
// If field out of range do nothing
// If game if finished do nothing
void MinesweeperBoard::toggleFlag(int row, int col) {
    if(!this->board[row][col].isRevealed){
        if(!this->board[row][col].hasFlag)
        this->board[row][col].hasFlag = true;
    }else {
        this->board[row][col].hasFlag = false;
    }



    if((row > this->height || row < 0) || (col > this->width || col < 0)){
        return;
    }

    if(this->gameState == FINISHED_LOSS || this->gameState == FINISHED_WIN){
        return;
    }
}
// If field was already revealed do nothing
// If either row or col is outside board do nothing
// If game is already finished do nothing
// If there is a flag on the field do nothing
void MinesweeperBoard::revealField(int row, int col) {
    if(this->board[row][col].isRevealed){
        return;
    }
    if((row > this->height || row < 0) || (col > this->width || col < 0)){
        return;
    }

    if(this->gameState == FINISHED_LOSS || this->gameState == FINISHED_WIN){
        return;
    }
    if(this->board[row][col].hasFlag){
        return;
    }

    if(!this->board[row][col].isRevealed){
        if(!this->board[row][col].hasMine){
            this->board[row][col].isRevealed = true;
            firstMove = false;
        }else{
            if(firstMove){
                this->board[row][col].hasMine = false;
                this->board[row][col].isRevealed = true;
                createRandomMine();
                firstMove = false;
            }
            else{
                this->board[row][col].isRevealed = true;
                this->gameState = FINISHED_LOSS;
            }
        }


    }


}
// Inline function to create on a random field a mine
// if mine already is on the field choose another field until free field is found
void MinesweeperBoard::createRandomMine() {
    //Variables to store randomly generated indexes
    int rHeight = rand() % height;
    int rWidth  = rand() % width;
    // Loop continues while field doesn't have mines on it
    while (!this->board[rHeight][rWidth].hasMine){
        // If the field doesn't have a mine put there a mine
        if (!this->board[rHeight][rWidth].hasMine) {
            this->board[rHeight][rWidth].hasMine = true;
        }
            // If field has a mine create new random indexes and repeat the loop
        else {
            srand(time(0));
            rHeight = rand() % height;
            rWidth = rand() % width;
            continue;
        }
    }
}

bool MinesweeperBoard::isRevealed(int row, int col) const {
    if(this->board[row][col].isRevealed)
        return true;

    return false;
}

// Iterates through the board and is there is revealed field with a mine
// Game is concidered to be lost
// If loop finds unrevealed field with no mine means game is still
// running, but if it finds unrevealed field with a mine it decrements mine
// counter inside the function and when it reaches 0 it means all field which are
// unrevealed have mines so the game is won
GameState MinesweeperBoard::getGameState() const {
    int mineCapacity = getMineCount();
    while(true){
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                if(this->board[i][j].hasMine && this->board[i][j].isRevealed)
                    return FINISHED_LOSS;
                if(!this->board[i][j].isRevealed){
                    if(!this->board[i][j].hasMine)
                        return RUNNING;
                    else{
                        mineCapacity--;
                    }
                }
                if(mineCapacity <= 0 )
                    return FINISHED_WIN;
            }
        }
        break;
    }
    return RUNNING;

}
// if row or col is outside board                         - return '#' character
// if the field is not revealed and has a flag            - return 'F' character
// if the field is not revealed and does not have a flag  - return '_' (underscore) character
// if the field is revealed and has mine                  - return 'x' character
// if the field is revealed and has 0 mines around        - return ' ' (space) character
// if the field is revealed and has some mines around     - return '1' ... '8' (number of mines as a digit)
char MinesweeperBoard::getFieldInfo(int row, int col) const {
    if((row > this->height || row < 0) || (col > this->width || col < 0)){
        return '#';
    }
    if(!this->board[row][col].isRevealed){
        if(this->board[row][col].hasFlag){
            return 'F';
        }else{
            return '_';
        }
    }else{
        if(this->board[row][col].hasMine){
            return 'x';
        }
        if(countMines(row,col) == 0){
            return ' ';
        }else {
            return (char)countMines(row,col)+'0';
        }
    }
}

void MinesweeperBoard::printAllFieldInfo() const {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            std::cout << '['<< getFieldInfo(i,j) << "]";
        }
        std::cout << std::endl;
    }

}



