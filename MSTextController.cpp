//
// Created by Luka Mitrović on 30/03/2021.
//

#include "MSTextController.h"
#include <iostream>

MSTextController::MSTextController(MSBoardTextView &view, MinesweeperBoard &board):
gameView(&view),gameBoard(&board){}

void MSTextController::play() {
    char commandCharacter;
    int row, col;
    gameView->display();
    std::cout << "Enter the command: \n F - put flag \n R - reveal field \n";
    std::cin >> commandCharacter;
    switch(commandCharacter){
        case 'F':
            std::cout << "Enter the row: ";
            std::cin >> row;
            std::cout << "Enter the column: ";
            std::cin >> col;
            gameBoard->toggleFlag(row,col);
            if(gameBoard->getGameState() == RUNNING)
            {std::cout << "RUNNING" << std::endl;}
            else if(gameBoard->getGameState() == FINISHED_WIN){
                std::cout << "FINISHED WIN" << std::endl;
            }else if(gameBoard->getGameState() == FINISHED_LOSS){
                std::cout << "FINISHED LOSS" << std::endl;
            }
            break;
        case 'R':
            std::cout << "Enter the row: ";
            std::cin >> row;
            std::cout << "Enter the column: ";
            std::cin >> col;
            gameBoard->revealField(row,col);
            if(gameBoard->getGameState() == RUNNING)
            {std::cout << "RUNNING" << std::endl;}
            else if(gameBoard->getGameState() == FINISHED_WIN){
                std::cout << "FINISHED WIN" << std::endl;
            }else if(gameBoard->getGameState() == FINISHED_LOSS){
                std::cout << "FINISHED LOSS" << std::endl;
            }
            break;
        default: std::cout << "Enter a proper command\n";
            break;
    }

}




