//
// Created by Luka Mitrović on 30/03/2021.
//

#include "MSBoardTextView.h"
#include <iostream>

MSBoardTextView::MSBoardTextView(MinesweeperBoard &board):gameBoard(&board){}

void MSBoardTextView::display() {
        for (int i = 0; i < gameBoard->getBoardHeight(); ++i) {
            for (int j = 0; j < gameBoard->getBoardWidth(); ++j) {
                std::cout << '['<< gameBoard->getFieldInfo(i,j) << "]";
            }
            std::cout << std::endl;
        }
            std::cout << std::endl;
    }





