//
// Created by Luka Mitrović on 30/03/2021.
//

#ifndef MINESAPER_MSBOARDTEXTVIEW_H
#define MINESAPER_MSBOARDTEXTVIEW_H
#include "MinesweeperBoard.h"

class MSBoardTextView {
    MinesweeperBoard *gameBoard;
public:
    MSBoardTextView(MinesweeperBoard &board);
    void display();

};


#endif //MINESAPER_MSBOARDTEXTVIEW_H
