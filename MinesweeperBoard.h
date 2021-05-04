//
// Created by Luka Mitrović on 23/03/2021.
//

#ifndef MINESAPER_MINESWEEPERBOARD_H
#define MINESAPER_MINESWEEPERBOARD_H

enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
    Field();
    Field(bool setMine);
    Field(unsigned short int a, unsigned short int b);
};

class MinesweeperBoard {
    Field board[100][100];    // 100-elementowa tablica, 100-elementowych tablic typu Field
    int width;                // rzeczywista szerokość planszy
    int height;               // rzeczywista wysokość planszy
    GameMode mode;            // Tryb gry
    GameState gameState;
    bool firstMove;
    int mineCount;
public:
    MinesweeperBoard(int width,int height);
    MinesweeperBoard(int width, int height, GameMode mode );


    static void createBoard(MinesweeperBoard& mb);
    void debug_display(MinesweeperBoard& mb) const;

    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    inline void createRandomMine();

    int countMines(int row, int col) const;
    bool hasFlag(int row, int col) const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);
    bool isRevealed(int row, int col) const;

    GameState getGameState() const;
    char getFieldInfo(int row, int col) const;
    void printAllFieldInfo() const;

};


#endif //MINESAPER_MINESWEEPERBOARD_H
