//
// Created by Luka Mitrović on 30/03/2021.
//

#ifndef MINESAPER_MSTEXTCONTROLLER_H
#define MINESAPER_MSTEXTCONTROLLER_H
#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"

class MSTextController {
    MinesweeperBoard *gameBoard;
    MSBoardTextView *gameView;
public:
    void play();
    MSTextController(MSBoardTextView &view , MinesweeperBoard &board);
};


#endif //MINESAPER_MSTEXTCONTROLLER_H
